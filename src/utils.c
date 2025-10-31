/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:11:33 by dt                #+#    #+#             */
/*   Updated: 2025/10/31 16:49:20 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t get_time(void)
{
	struct timeval tv;
	uint64_t sec_ms;
	uint64_t usec_ms;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	sec_ms = (uint64_t)tv.tv_sec * 1000ULL;
	usec_ms = (uint64_t)tv.tv_usec / 1000ULL;
	return (sec_ms + usec_ms);
}

void	writing_function(t_table *t_table, int id, char *status)
{
	pthread_mutex_lock(&t_table->writing);
	if (is_simulation_running(t_table))
		printf("%lu %d %s\n", get_time() - t_table->start_time, id, status);
	pthread_mutex_unlock(&t_table->writing);
}

void take_forks(t_philosofer *philo)
{
	int left;
	int right;

	left = philo->id - 1;
	right = philo->id % philo->table->num_phil;
	if (!is_simulation_running(philo->table))
    	return;
	/* lock in consistent order to reduce deadlock risk */
	if (left < right)
	{
		pthread_mutex_lock(&philo->table->forks[left]);
		writing_function(philo->table, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[right]);
		writing_function(philo->table, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[right]);
		writing_function(philo->table, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[left]);
		writing_function(philo->table, philo->id, "has taken a fork");
	}
}

void put_down_forks(t_philosofer *philo)
{
    int left_fork;
    int right_fork;

    left_fork = philo->id - 1;
    right_fork = philo->id % philo->table->num_phil;

    pthread_mutex_unlock(&philo->table->forks[left_fork]);
    pthread_mutex_unlock(&philo->table->forks[right_fork]);
}

void philo_eat(t_philosofer *philo)
{
	pthread_mutex_lock(&philo->data_mutex);
	philo->now_is_eating = true;
	philo->last_eat = get_time();
	philo->eaten_meals = philo->eaten_meals + 1;
	pthread_mutex_unlock(&philo->data_mutex);
	writing_function(philo->table, philo->id, "is eating");
	wait_action_to_end(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->data_mutex);
    philo->now_is_eating = false;
    pthread_mutex_unlock(&philo->data_mutex);
}
