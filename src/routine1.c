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
	philo_thinking();
	if (philo->table->num_phil % 2 == 0)
	{
		if (philo->id % 2 == 0)
			even_n_philo(philo->table->time_to_eat);
	}
	else
	{
		if (philo->id == philo->table->num_phil)
			odd_n_philo(philo);
		else if (philo->id % 2 == 0)
			even_n_philo(philo->table->time_to_eat);
	}
}

static void	philosopher_life_cycle(t_philosofer *philo)
{
	while (is_simulation_running(philo->table))
	{
		writing_function(philo->table, philo->id, "is thinking");
		philo_thinking();
		take_forks(philo);
		philo_eat(philo);
		put_down_forks(philo);
		writing_function(philo->table, philo->id, "is sleeping");
		philo_sleep(philo);
		if (is_dinner_over(philo))
			break ;
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
