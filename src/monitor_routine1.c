/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:53:37 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/03 20:05:41 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_for_deaths(t_table *table)
{
	t_philosofer	*philo;
	int				i;

	i = 0;
	while (i < table->num_phil)
	{
		philo = &table->philos[i];
		if (check_philosopher_death(philo))
		{
			writing_function(table, table->philos[i].id, "died");
			stop_simulation(table);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_simulation_end(t_table *table)
{
	if (check_all_philosophers_full(table))
	{
		stop_simulation(table);
		return (1);
	}
	return (0);
}

static void	monitor_loop(t_table *table)
{
	while (is_simulation_running(table))
	{
		if (check_for_deaths(table))
			return ;
		if (check_simulation_end(table))
			return ;
		usleep(1000);
	}
}

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	monitor_loop(table);
	return (NULL);
}
