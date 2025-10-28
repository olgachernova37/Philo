/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:11:33 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/28 19:46:03 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"



int initialize_arg(t_table *table,int argc, char **argv)
{
   table->n_philos = ft_atoi(argv[1]);
    table->time_to_die = (uint64_t)ft_atoi(argv[2]);
    table->time_to_eat = (uint64_t)ft_atoi(argv[3]);
    table->time_to_sleep = (uint64_t)ft_atoi(argv[4]);
    if (argc == 6)
        table->meals_required = ft_atoi(argv[5]);
    else
        table->meals_required = -1;

    table->start_time = 0;
    if (pthread_mutex_init(&table->writing, NULL) != 0)
    {
        free(table);
        return (0);
    }
    table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philos);
    if (!table->forks)
    {
        pthread_mutex_destroy(&table->writing);
        free(table);
        return (0);
    }
    return(1);
}


t_table	*create_table(int argc, char **argv)
{
    t_table	*table;
    int     i;

    table = (t_table *)malloc(sizeof(t_table));
    if (!table)
        return (NULL);

    if (!initialize_arg(table, argc, argv))
        return(NULL);
    
    return (table);  
}
