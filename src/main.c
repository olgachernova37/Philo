/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/07/28 20:22:24 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// int	main(int argc, char **argv)


// {
	
// 	return (0);
// }

#include <pthread.h>
pthread_mutex_t balance_mutex = PTHREAD_MUTEX_INITIALIZER;

// the initial balance is 0
int balance = 0;

// write the new balance (after as simulated 1/4 second delay)
void write_balance(int new_balance)
{
  usleep(250000);
  pthread_mutex_lock(&balance_mutex);
  balance = new_balance;
  pthread_mutex_unlock(&balance_mutex);
}

// returns the balance (after a simulated 1/4 seond delay)
int read_balance()
{
  usleep(250000);
  pthread_mutex_lock(&balance_mutex);
  int b = balance;
  pthread_mutex_unlock(&balance_mutex);
  return b;
}

// carry out a deposit
void* deposit(void *amount)
{
  pthread_mutex_lock(&balance_mutex);

  int account_balance = balance;
  account_balance += *((int *) amount);
  balance = account_balance;

  pthread_mutex_unlock(&balance_mutex);

  return NULL;
}

int main()
{
  // output the balance before the deposits
  int before = read_balance();
  printf("Before: %d\n", before);

  // we'll create two threads to conduct a deposit using the deposit function
  pthread_t thread1;
  pthread_t thread2;

  // the deposit amounts... the correct total afterwards should be 500
  int deposit1 = 300;
  int deposit2 = 200;

  // create threads to run the deposit function with these deposit amounts
  pthread_create(&thread1, NULL, deposit, (void*) &deposit1);
  pthread_create(&thread2, NULL, deposit, (void*) &deposit2);

  // join the threads
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  // output the balance after the deposits
  int after = read_balance();
  printf("After: %d\n", after);

  return 0;
}



