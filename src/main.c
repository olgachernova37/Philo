/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:53 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/30 19:32:07 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	main(int argc, char const **argv)
{
    t_table	*table;

    if (checking_input(argc, argv) == -1)
        return (1);
    table = create_table(argc, (char **)argv);
    if (!table)
    {
        printf("Failed to init table\n");
        return (1);
    }
    // 3) spawn philosophers (creates threads running philosopher_routine)
    if (spawn_philosophers(table) != 0)
    {
        destroy_table(table);
        return (1);
    }

    // 4) monitor / join threads (spawnum_philophers can join or return threads to join here)
    // implement monitor to detect death/finish, then cleanup

    destroy_table(table);
    return (0);
}





// // init
// table->forks = malloc(sizeof(pthread_mutex_t) * table->num_phil);
// for (int i = 0; i < table->num_phil; ++i)
//     pthread_mutex_init(&table->forks[i], NULL);

// // philosopher takes forks (id is 1..n)
// int left = philo->id - 1;
// int right = philo->id % table->num_phil;
// /* lock in consistent order to reduce deadlock risk */
// if (left < right) {
//     pthread_mutex_lock(&table->forks[left]);
//     pthread_mutex_lock(&table->forks[right]);
// } else {
//     pthread_mutex_lock(&table->forks[right]);
//     pthread_mutex_lock(&table->forks[left]);
// }
// /* eat */
// pthread_mutex_unlock(&table->forks[left]);
// pthread_mutex_unlock(&table->forks[right]);

// // cleanup
// for (int i = 0; i < table->num_phil; ++i)
//     pthread_mutex_destroy(&table->forks[i]);
// free(table->forks);