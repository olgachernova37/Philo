/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:00:15 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/03 20:03:14 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// parni
void	even_n_philo(uint64_t time_in_ms)
{
	ft_usleep(time_in_ms / 2);
}

void	wait_action_to_end(uint64_t duration_ms)
{
	ft_usleep(duration_ms);
}

// neparni
void	odd_n_philo(t_philosofer *philo)
{
	uint64_t	delay_time;

	if (philo->table->time_to_eat > philo->table->time_to_sleep)
		delay_time = philo->table->time_to_eat + (philo->table->time_to_sleep
				/ 3);
	else
		delay_time = (philo->table->time_to_eat * 4) / 3;
	delay_time += (philo->id * 10);
	wait_action_to_end(delay_time);
}

void	philo_thinking(void)
{
	usleep(500);
}
