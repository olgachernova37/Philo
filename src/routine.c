/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:00:15 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/30 22:20:21 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//parni
void even_n_philo(uint64_t time_in_ms)
{
        long long	start;
        uint16_t delay;

        delay = time_in_ms / 2;
	    start = get_time();
	    while (get_time() - start < time_in_ms)
		usleep(delay);
}

void accurate_sleep(uint64_t duration_ms)
{
    uint64_t start_time;
    uint64_t elapsed;
    
    start_time = get_time();
    while (1)
    {
        elapsed = get_time() - start_time;
        if (elapsed >= duration_ms)
            break;
        usleep((duration_ms - elapsed) * 100);
    }
}

//neparni
void odd_n_philo(t_philosofer *philo)
{
     uint64_t delay_time;
    
    // Базова затримка залежить від позиції філософа
    if (philo->table->time_to_eat > philo->table->time_to_sleep)
        delay_time = philo->table->time_to_eat + (philo->table->time_to_sleep / 3);
    else
        delay_time = (philo->table->time_to_eat * 4) / 3;
    
    // Додаткова затримка для останнього філософа
    delay_time += (philo->id * 10);
    
    accurate_sleep(delay_time);
}


void philo_thinking()
{
    usleep(100); // Simulate thinking time
}


void	*philosopher_routine(void *arg)
{
	t_philosofer	*philo;

	philo = (t_philosofer *)arg;
    //if philo is one write by mutex writing "has taken a fork" and 
    if (philo->table->num_phil == 1)
		return (writing_function(philo->table, philo->id, "has taken a fork"), NULL);
    
    
    philo_thinking();
    if (philo->table->num_phil % 2 == 0)
        even_n_philo(philo->table->time_to_eat);
    if (philo->table->num_phil % 2 == 1 && philo->id == philo->table->num_phil)
        odd_n_philo(philo);
    while (is_simulation_running(philo->table))
    {
        // 1. THINKING
        writing_function(philo->table, philo->id, "is thinking");
        philo_thinking();
        take_forks(philo);
        philo_eat(philo);
        // 5. SLEEPING
        writing_function(philo->table, philo->id, "is sleeping");
        philo_sleep(philo);
        
        // 6. CHECK CONDITIONS
        if (is_dinner_over(philo))
            break;
    }
    return (NULL);
}
