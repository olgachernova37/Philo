/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:53:37 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/31 17:32:32 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void stop_simulation(t_table *table)
{
    void stop_simulation(t_table *table)
{
    pthread_mutex_lock(&table->simulation_mutex);
    table->simulation_active = 0;
    pthread_mutex_unlock(&table->simulation_mutex);
}
}

int check_philosopher_death(t_philosofer *philo)
{
    uint64_t time_from_last_meal;
    uint64_t time_now;
     uint64_t copy_last_meal;

    time_now = get_time();
    pthread_mutex_lock(&philo->data_mutex);
    copy_last_meal = philo->last_eat;  // ✅ Безпечно скопіювати
    pthread_mutex_unlock(&philo->data_mutex);
    time_from_last_meal = time_now - copy_last_meal;
    if (time_from_last_meal> philo->table->time_to_die)
        return 1;
    return 0;
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
                writing_function(table, table->philos[i].id, "died");
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
