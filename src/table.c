/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:11:33 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/30 19:32:43 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void destroy_table(t_table *table)
{
    int i;

    if (!table)
        return ;
    if (table->philos)
    {
        i = 0;
        while (i < table->num_phil)
            pthread_mutex_destroy(&table->philos[i++].data_mutex);
        free(table->philos);
    }
    if (table->forks)
    {
        i = 0;
        while (i < table->num_phil)
            pthread_mutex_destroy(&table->forks[i++]);
        free(table->forks);
    }
    pthread_mutex_destroy(&table->writing);
    free(table);
}

void	cleanup_on_forks_init_fail(t_table *table, int initialized)
{
    int i;

    if (table->forks)
    {
        i = 0;
        while (i < initialized)
            pthread_mutex_destroy(&table->forks[i++]);
        free(table->forks);
    }
    pthread_mutex_destroy(&table->writing);
    free(table);
}

int initialize_arg2(t_table *table,int argc, char **argv)
{
    int i;

    (void)argc;
    (void)argv;
    if (!table || !table->forks)
        return (0);
    i = 0;
    while (i < table->num_phil)
    {
        if (pthread_mutex_init(&table->forks[i], NULL) != 0)
        {
            cleanup_on_forks_init_fail(table, i);
            return (0);
        }
        i++;
    }
    return (1);
}

int initialize_arg(t_table *table,int argc, char **argv)
{
    table->num_phil = ft_atoi(argv[1]);
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
    table->forks = malloc(sizeof(pthread_mutex_t) * table->num_phil);
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

    table = (t_table *)malloc(sizeof(t_table));
    if (!table)
        return (NULL);

    if (!initialize_arg(table, argc, argv))
        return(NULL);
    if (!initialize_arg2(table, argc, argv))
        return(NULL);
    if (!initialize_philos(table))
        return(NULL);    
    return (table);  
}

