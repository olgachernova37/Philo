/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:00:15 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/03 20:02:32 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_single_philosopher(t_philosofer *philo)
{
	if (philo->table->num_phil == 1)
	{
		writing_function(philo->table, philo->id, "has taken a fork");
		return (1);
	}
	return (0);
}

static void	initialize_philosopher_timing(t_philosofer *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(philo->table->time_to_eat);
}

static void	philosopher_life_cycle(t_philosofer *philo)
{
	uint64_t	margin;

	margin = philo->table->time_to_die - (philo->table->time_to_eat
			+ philo->table->time_to_sleep);
	while (is_simulation_running(philo->table))
	{
		writing_function(philo->table, philo->id, "is thinking");
		if (margin > philo->table->time_to_eat && philo->table->num_phil < 200)
			philo_thinking();
		if (!take_forks(philo))
			break ;
		philo_eat(philo);
		put_down_forks(philo);
		if (is_dinner_over(philo))
			break ;
		writing_function(philo->table, philo->id, "is sleeping");
		philo_sleep(philo);
	}
}

void	*philosopher_routine(void *arg)
{
	t_philosofer	*philo;

	philo = (t_philosofer *)arg;
	if (handle_single_philosopher(philo))
		return (NULL);
	initialize_philosopher_timing(philo);
	philosopher_life_cycle(philo);
	return (NULL);
}
