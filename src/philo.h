/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:31:21 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/30 22:21:41 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdint.h> // uint64_t type
# include <unistd.h> // usleep
# include <string.h>
# include <pthread.h>
# include <stdio.h> //printf
# include <stdlib.h> //malloc
# include <sys/time.h> // gettimeofday
#include <stdbool.h>
# include "../libs/libft/libft.h"
# include "../libs/libftprintf/ft_printf.h"

// # include <sys/types.h> // u_int64_t type

// typedef struct s_struct_fork
// {
//     //number and mutex

// } t_struct_fork;

typedef struct s_philosofer
{
	int				id;
	pthread_t		thread;
	// t_struct_fork			*left_fork;
	// t_struct_fork			*right_fork;
	uint64_t			last_eat;
    bool			now_is_eating;//t_bool
	int				eaten_meals;
	pthread_mutex_t	data_mutex;
	struct s_table	*table;
}	t_philosofer;

typedef struct s_table
{
    int				num_phil;
    uint64_t		time_to_die;
    uint64_t		time_to_eat;
    uint64_t		time_to_sleep;
    int				meals_to_eat; // -1 if not provided
    pthread_mutex_t	*forks;         // array size num_phil
    pthread_mutex_t	writing;
    uint64_t		start_time;
    t_philosofer	*philos;        // array size num_phil
    int             simulation_active;    // Чи працює симуляція
    pthread_mutex_t simulation_mutex; 
     // int           simulation_running;  // flag to stop simulation
    // pthread_t     monitor_thread;      // monitor thread handle
    // pthread_mutex_t simulation_mutex;  // protect simulation_running flag
}	t_table;

// main.c


// parsing.c
int		checking_input(int argc, char const **argv);
int		is_digits_separated_by_spaces(const char *s);
int is_simulation_running(t_table *table);

//utils.c
uint64_t get_time(void);
void	writing_function(t_table *t_table, int id, char *status);
void take_forks(t_philosofer *philo);
void philo_eat(t_philosofer *philo);

// philo_init.c
int		initialize_philos(t_table *table);
void    cleanup_on_philos_init_fail(t_table *table, int philos_inited);
void    initialize_elements_of_philos(t_table *table, int index);
int		spawn_philosophers(t_table *table);

// table.c 5
t_table	*create_table(int argc, char **argv);
int		initialize_arg(t_table *table, int argc, char **argv);
int		initialize_arg2(t_table *table, int argc, char **argv);
void     destroy_table(t_table *table);
void cleanup_on_forks_init_fail(t_table *table, int forks_inited);

// routine.c 5
void    philo_thinking();
void	*philosopher_routine(void *arg);
void    even_n_philo(uint64_t time_in_ms);
void    odd_n_philo(t_philosofer *philo);
void    accurate_sleep(uint64_t duration_ms);
#endif
