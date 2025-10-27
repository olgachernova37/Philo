/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/27 16:58:12 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int is_digits_separated_by_spaces(char** str)
{
	int i;
	if (!str || str[0] == '\0')
        return (0);
    if (str[0] == ' ')
        return (0);
    i = ft_strlen(str);
    if (i > 0 && str[i - 1] == ' ')
        return (0);
    i = 0;
    while (str[i])
    {
        if (isdigit(str[i]))
			i++;
        else if (str[i] == ' ')
        {
            /* next must be a digit (no consecutive spaces, no trailing space) */
            if (str[i + 1] == '\0' || !isdigit(str[i + 1]))
                return (0);
			i++;
        }
        else
            return (0);
    }
    return (1);
}

int checking_input(int argc, char const **argv)
{	
	int i;

	i=0;
	if (argc != 5 && argc != 6)
	{
		printf("Wrong number of argumnets");
		return (-1);
	}
	while(argv[i])
	{
		if(is_digits_separated_by_spaces(argv[i]))
			printf("All good");
	}
	
	
}

int	main(int argc, char const **argv)
{
	int	i;

	i = checking_input(argc, argv);
	if (i == -1)
		return (-1);
	printf("%s\n", argv[1]);
	return (0);
}

// #include <pthread.h>

// pthread_mutex_t	balance_mutex = PTHREAD_MUTEX_INITIALIZER;

// // the initial balance is 0
// int				balance = 0;

// // write the new balance (after as simulated 1/4 second delay)
// void	write_balance(int new_balance)
// {
// 	usleep(250000);
// 	pthread_mutex_lock(&balance_mutex);
// 	balance = new_balance;
// 	pthread_mutex_unlock(&balance_mutex);
// }

// // returns the balance (after a simulated 1/4 seond delay)
// int	read_balance(void)
// {
// 	int	b;

// 	usleep(250000);
// 	pthread_mutex_lock(&balance_mutex);
// 	b = balance;
// 	pthread_mutex_unlock(&balance_mutex);
// 	return (b);
// }

// // carry out a deposit
// void	*deposit(void *amount)
// {
// 	int	account_balance;

// 	pthread_mutex_lock(&balance_mutex);
// 	account_balance = balance;
// 	account_balance += *((int *)amount);
// 	balance = account_balance;
// 	pthread_mutex_unlock(&balance_mutex);
// 	return (NULL);
// }

// int	main(void)
// {
// 	int			before;
// 	pthread_t	thread1;
// 	pthread_t	thread2;
// 	int			deposit1;
// 	int			deposit2;
// 	int			after;

// 	// output the balance before the deposits
// 	before = read_balance();
// 	printf("Before: %d\n", before);
// 	// we'll create two threads to conduct a deposit using the deposit function
// 	// the deposit amounts... the correct total afterwards should be 500
// 	deposit1 = 300;
// 	deposit2 = 200;
// 	// create threads to run the deposit function with these deposit amounts
// 	pthread_create(&thread1, NULL, deposit, (void *)&deposit1);
// 	pthread_create(&thread2, NULL, deposit, (void *)&deposit2);
// 	// join the threads
// 	pthread_join(thread1, NULL);
// 	pthread_join(thread2, NULL);
// 	// output the balance after the deposits
// 	after = read_balance();
// 	printf("After: %d\n", after);
// 	return (0);
// }
