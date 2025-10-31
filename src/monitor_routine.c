/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:53:37 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/31 17:16:01 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_philosopher_death(t_philosofer *philo)
{
    uint64_t time_from_last_meal;
    uint64_t time_now;

    time_now = get_time();
    

    
}

void *monitor_routine(void *arg)
{
    t_table		*table;
    t_philosofer	*philo;
    int			i;

    i = 0;
    table = (t_table *)arg;
    while (is_simulation_running(table))
    {
        
        while (i < table->num_phil)
        {
            philo = &table->philos[i];
            if (check_philosopher_death(philo))
            {
                stop_simulation(table);
                return (NULL);
            }
            i++;
        }
        if (is_dinner_over(table))
        {
            stop_simulation(table);
            return (NULL);
        }
        usleep(1000); // Sleep for 1 ms to reduce CPU usage
    }
    return (NULL);
}