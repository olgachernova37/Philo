/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:31:21 by olcherno          #+#    #+#             */
/*   Updated: 2025/11/03 17:50:10 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libs/libft/libft.h"
# include "../libs/libftprintf/ft_printf.h"
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philosofer
{
	int				id;
	pthread_t		thread;
	uint64_t		last_eat;
	bool			now_is_eating;
	int				eaten_meals;
	pthread_mutex_t	data_mutex;
	struct s_table	*table;
}					t_philosofer;

typedef struct s_table
{
	int				num_phil;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				meals_to_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing;
	uint64_t		start_time;
	t_philosofer	*philos;
	int				simulation_active;
	pthread_mutex_t	simulation_mutex;
	pthread_t		inspector;

}					t_table;

// parsing.c
int					checking_input(int argc, char const **argv);
int					is_digits_separated_by_spaces(const char *s);
int					is_simulation_running(t_table *table);
int					is_dinner_over(t_philosofer *philo);

// utils.c 6
uint64_t			get_time(void);
void				ft_usleep(uint64_t time_in_ms);
void				writing_function(t_table *t_table, int id, char *status);
int					take_forks(t_philosofer *philo);
void				philo_eat(t_philosofer *philo);
void				put_down_forks(t_philosofer *philo);

// philo_init.c 5
int					initialize_philos(t_table *table);
void	cleanup_on_philos_init_fail(t_table *table,
									int philos_inited);
void				initialize_elements_of_philos(t_table *table, int index);
int					spawn_philosophers(t_table *table);
void				philo_sleep(t_philosofer *philo);

// table.c 5
t_table				*create_table(int argc, char **argv);
int					initialize_arg(t_table *table, int argc, char **argv);
int					initialize_arg2(t_table *table, int argc, char **argv);
void				destroy_table(t_table *table);
void	cleanup_on_forks_init_fail(t_table *table,
								int forks_inited);

// philo routine.c 5
void				philo_thinking(void);
void				*philosopher_routine(void *arg);
void				even_n_philo(uint64_t time_in_ms);
void				odd_n_philo(t_philosofer *philo);
void				wait_action_to_end(uint64_t duration_ms);

// monitor.c 5
void				*monitor_routine(void *arg);
int					check_philosopher_death(t_philosofer *philo);
int					check_all_philosophers_full(t_table *table);
void				stop_simulation(t_table *table);

#endif
