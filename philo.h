/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:31:21 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/28 19:54:17 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdint.h> // uint64_t type
# include <unistd.h> // usleep
# include <string.h>
# include <pthread.h>
# include <stdio.h> //printf
# include <stdlib.h> //malloc
# include <sys/time.h> // gettimeofday
// # include <sys/types.h> // u_int64_t type

typedef struct s_philosofer
{
	int				id;
	pthread_t		thread;
	// t_fork			*left_fork;
	// t_fork			*right_fork;
	// long			last_fed;
	// int				meals_eaten;
	//t_bool			now_eating;
	pthread_mutex_t	data_mutex;
	struct s_table	*table;
}	t_philosofer;

typedef struct s_table
{
    int				n_philos;
    uint64_t		time_to_die;
    uint64_t		time_to_eat;
    uint64_t		time_to_sleep;
    int				meals_required; // -1 if not provided
    pthread_mutex_t	*forks;         // array size n_philos
    pthread_mutex_t	writing;
    uint64_t		start_time;
    t_philosofer	*philos;        // array size n_philos
}	t_table;

// prototypes
t_table	*create_table(int argc, char **argv);
void	destroy_table(t_table *table);
int		spawn_philosophers(t_table *table);
void	*philosopher_routine(void *arg);
int	initialize_arg(t_table *table,int argc, char **argv);

#endif
