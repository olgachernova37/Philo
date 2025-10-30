/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:50:50 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/30 20:00:50 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	cleanup_on_philos_init_fail(t_table *table, int philos_inited)
{
    int i;

    if (table->philos)
    {
        i = 0;
        while (i < philos_inited)
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

void initialize_elements_of_philos(t_table *table, int index)
{
    table->philos[index].id = index + 1;
    table->philos[index].table = table;
    table->philos[index].thread = 0;           // will be set in spawn_philosophers
    table->philos[index].last_eat = 0;   // will be set to start_time when simulation begins
    table->philos[index].eaten_meals = 0;
    table->philos[index].now_is_eating = false;
    
}

int initialize_philos(t_table *table)
{
    int index;

    index=0;
    table->philos = malloc(sizeof(t_philosofer) * table->num_phil);
    if (!table->philos)
        return (0);
    while (index <table->num_phil)
    {
        initialize_elements_of_philos(table, index);
        if (pthread_mutex_init(&table->philos[index].data_mutex, NULL) != 0)
    {
        cleanup_on_philos_init_fail(table, index);
        return (0);
    }
        index++;
    }
    return(1);
}

int spawn_philosophers(t_table *table)
{
    // Placeholder implementation
    // Actual implementation would create threads for each philosopher
    int index;

    index = 0;
    table->start_time = get_time(); // Set to current time in actual implementation
    while(index < table->num_phil)
    {
        // Here you would create the thread for each philosopher
        table->philos[index].last_eat = table->start_time;
        if (pthread_create(&table->philos[index].thread, NULL, philosopher_routine(index), &table->philos[index]) != 0)
        {
            // Handle thread creation failure
            cleanup_created_threads(table, index);  // Clean up threads 0 to index-1
            return (0); // Return failure
        }
        index++;
    }
    return (0); // Return 0 on success
}

