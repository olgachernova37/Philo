/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:53:37 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/03 20:08:09 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	stop_simulation(t_table *table)
{
	pthread_mutex_lock(&table->simulation_mutex);
	table->simulation_active = 0;
	pthread_mutex_unlock(&table->simulation_mutex);
}

int	check_all_philosophers_full(t_table *table)
{
	int	i;
	int	full_count;
	int	eaten_meals;

	if (table->meals_to_eat <= 0)
		return (0);
	full_count = 0;
	i = 0;
	while (i < table->num_phil)
	{
		pthread_mutex_lock(&table->philos[i].data_mutex);
		eaten_meals = table->philos[i].eaten_meals;
		pthread_mutex_unlock(&table->philos[i].data_mutex);
		if (eaten_meals >= table->meals_to_eat)
			full_count++;
		i++;
	}
	return (full_count == table->num_phil);
}

int	check_philosopher_death(t_philosofer *philo)
{
	uint64_t	time_from_last_meal;
	uint64_t	time_now;
	uint64_t	copy_last_meal;

	time_now = get_time();
	pthread_mutex_lock(&philo->data_mutex);
	copy_last_meal = philo->last_eat;
	pthread_mutex_unlock(&philo->data_mutex);
	time_from_last_meal = time_now - copy_last_meal;
	if (time_from_last_meal > philo->table->time_to_die)
		return (1);
	return (0);
}
