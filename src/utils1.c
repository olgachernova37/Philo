/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:11:33 by dt                #+#    #+#             */
/*   Updated: 2025/11/03 19:59:48 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks_in_order(t_philosofer *philo, int first, int second)
{
	pthread_mutex_lock(&philo->table->forks[first]);
	if (!is_simulation_running(philo->table))
	{
		pthread_mutex_unlock(&philo->table->forks[first]);
		return (0);
	}
	writing_function(philo->table, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->table->forks[second]);
	if (!is_simulation_running(philo->table))
	{
		pthread_mutex_unlock(&philo->table->forks[first]);
		pthread_mutex_unlock(&philo->table->forks[second]);
		return (0);
	}
	writing_function(philo->table, philo->id, "has taken a fork");
	return (1);
}

static void	determine_fork_order(t_philosofer *philo, int *first, int *second)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->table->num_phil;
	if (left < right)
	{
		*first = left;
		*second = right;
	}
	else
	{
		*first = right;
		*second = left;
	}
}

int	take_forks(t_philosofer *philo)
{
	int	first_fork;
	int	second_fork;

	if (!is_simulation_running(philo->table))
		return (0);
	determine_fork_order(philo, &first_fork, &second_fork);
	return (take_forks_in_order(philo, first_fork, second_fork));
}
