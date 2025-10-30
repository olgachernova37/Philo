/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:11:33 by dt                #+#    #+#             */
/*   Updated: 2025/10/30 20:22:20 by olcherno         ###   ########.fr       */
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
