/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:48 by dt                #+#    #+#             */
/*   Updated: 2025/10/30 21:33:41 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_digits_separated_by_spaces(const char *s)
{
    int i;

    if (!s)
        return (0);
    i = 0;
    while (s[i])
    {
        if (!(ft_isdigit((int)(unsigned char)s[i]) || s[i] == ' '))
        {
            printf("Argument should be digits separated by spaces\n");
            return (0);
        }
        i++;
    }
    return (1);
}

int checking_input(int argc, char const **argv)
{	
    int i;

    if ((argc != 5 && argc != 6) || argv == NULL || argc > 200)
    {
        printf("Wrong number of arguments\n");
        return (-1);
    }
	if(ft_atoi(argv[1]) <= 0)
	{
		printf("Number of philosophers must be positive\n");
		return (-1);
	}
    i = 1;
    while (argv[i])
    {
        if (!is_digits_separated_by_spaces(argv[i]))
            return (0);
        i++;
    }
    return (1);
}

int is_simulation_running(t_table *table)
{
    int running;
    
    pthread_mutex_lock(&table->simulation_mutex);
    running = table->simulation_active;
    pthread_mutex_unlock(&table->simulation_mutex);
    return (running);
}

// uint64_t get_time(void)
// {
//     struct timeval tv;
//     gettimeofday(&tv, NULL);
//     return (tv.tv_sec * 1000 + tv.tv_usec / 1000); // milliseconds
// }