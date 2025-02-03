/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:05:32 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/03 10:10:27 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

/******************************************************************************
*                                   Macros                                    *
******************************************************************************/

# define MAX_PHILOS	200
# define STR_MAX_PHILOS "200"

# define STR_PROG_NAME	"philo:"
# define STR_USAGE	"%s usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define STR_ERR_THREAD	"%s error: Could not create thread.\n"
# define STR_ERR_MALLOC	"%s error: Could not allocate memory.\n"
# define STR_ERR_MUTEX	"%s error: Could not create mutex.\n"

/******************************************************************************
*                                 Structures                                  *
******************************************************************************/

typedef struct s_philo	t_philo;

typedef struct s_data
{
	time_t			start_time;
	unsigned int	nb_philos;
	pthread_t		grim_reaper;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat_count;
	bool			sim_stop;
	pthread_mutex_t	sim_stop_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
	t_philo			**philos;
}	t_data;

typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		times_ate;
	unsigned int		fork[2];
	pthread_mutex_t		meal_time_lock;
	time_t				last_meal;
	t_data				*data;
	bool				is_eating;
}	t_philo;

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	GOT_FORK_1 = 4,
	GOT_FORK_2 = 5
}	t_status;

/******************************************************************************
*                           Function Prototypes                               *
******************************************************************************/

//  ft_strncmp.c
int				ft_strncmp(const char *s1, const char *s2, int n);

//	parsing.c
bool			is_valid_input(char **av);
int				ft_atoi(char *str);

//	init.c
t_data			*init_data(int ac, char **av, int i);

//	routines.c
void			*philosopher(void *data);

//	time.c
time_t			get_time_in_ms(void);
void			philo_sleep(t_data *data, time_t sleep_time);
void			sim_start_delay(time_t start_time);

//	output.c
void			write_status(t_philo *philo, bool reaper, t_status status);

//	grim_reaper.c
void			*grim_reaper(void *data);
bool			has_simulation_stopped(t_data *data);

//	exit.c
int				msg(char *str, char *detail, int exit_no);
void			*error_null(char *str, char *details, t_data *data);
int				error_failure(char *str, char *details, t_data *data);
void			*free_data(t_data *data);
void			destroy_mutexes(t_data *data);

#endif
