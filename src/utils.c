/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:11:33 by dt                #+#    #+#             */
/*   Updated: 2025/10/30 22:16:07 by olcherno         ###   ########.fr       */
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
		printf("%lld %d %s\n", get_time() - t_table->start_time, id, status);
	pthread_mutex_unlock(&t_table->writing);
}

void take_forks(t_philosofer *philo)
{
	int left;
	int right;

	left = philo->id - 1;
	right = philo->id % philo->table->num_phil;
	/* lock in consistent order to reduce deadlock risk */
	if (left < right)
	{
		pthread_mutex_lock(&philo->table->forks[left]);
		pthread_mutex_lock(&philo->table->forks[right]);
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[right]);
		pthread_mutex_lock(&philo->table->forks[left]);
	}
}

void philo_eat(t_philosofer *philo)
{
	philo->now_is_eating = true;
	philo->last_eat = get_time();
	writing_function(philo->table, philo->id, "is eating");
	accurate_sleep(philo->table->time_to_eat);
	philo->eaten_meals += 1;
	philo->now_is_eating = false;
	pthread_mutex_unlock(&philo->table->forks[philo->id - 1]);
	pthread_mutex_unlock(&philo->table->forks[philo->id % philo->table->num_phil]);
}
