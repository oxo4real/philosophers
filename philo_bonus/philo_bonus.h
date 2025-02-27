/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:23:20 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/03 12:47:59 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <semaphore.h>
# include <signal.h>
# include <pthread.h>

/******************************************************************************
*                                     Macros                                  *
******************************************************************************/

# define MAX_PHILOS	200
# define STR_MAX_PHILOS "200"

# define STR_PROG_NAME	"philo_bonus:"
# define STR_USAGE	"%s usage: ./philo_bonus <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define STR_ERR_THREAD	"%s error: Could not create thread.\n"
# define STR_ERR_MALLOC	"%s error: Could not allocate memory.\n"
# define STR_ERR_SEM	"%s error: Could not create semaphore.\n"
# define STR_ERR_FORK	"%s error: Could not fork child.\n"

# define SEM_NAME_FORKS "/philo_global_forks"
# define SEM_NAME_WRITE "/philo_global_write"
# define SEM_NAME_FULL	"/philo_global_full"
# define SEM_NAME_DEAD	"/philo_global_dead"
# define SEM_NAME_STOP	"/philo_global_stop"
# define SEM_NAME_MEAL	"/philo_local_meal_"

# define CHILD_EXIT_ERR_PTHREAD	40
# define CHILD_EXIT_ERR_SEM		41
# define CHILD_EXIT_PHILO_FULL	42
# define CHILD_EXIT_PHILO_DEAD	43

/******************************************************************************
*                                 Structures                                  *
******************************************************************************/

typedef struct s_philo	t_philo;

typedef struct s_data
{
	time_t			start_time;
	unsigned int	nb_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat_count;
	sem_t			*sem_forks;
	sem_t			*sem_write;
	sem_t			*sem_philo_full;
	unsigned int	philo_full_count;
	sem_t			*sem_philo_dead;
	sem_t			*sem_stop;
	bool			stop_sim;
	t_philo			**philos;
	t_philo			*this_philo;
	pid_t			*pids;
	pthread_t		gluttony_reaper;
	pthread_t		famine_reaper;
}	t_data;

typedef struct s_philo
{
	pthread_t			personal_grim_reaper;
	sem_t				*sem_forks;
	sem_t				*sem_write;
	sem_t				*sem_philo_full;
	sem_t				*sem_philo_dead;
	sem_t				*sem_meal;
	char				*sem_meal_name;
	unsigned int		nb_forks_held;
	unsigned int		id;
	unsigned int		times_ate;
	bool				ate_enough;
	bool				is_eating;
	time_t				last_meal;
	t_data				*data;
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

//  ft_strncmp_bonus.c
int				ft_strncmp(const char *s1, const char *s2, int n);

//	main_bonus.c
bool			has_simulation_stopped(t_data *data);

//	parsing_bonus.c
bool			is_valid_input(char **av);
int				ft_atoi(char *str);

//	init_bonus.c
t_data			*init_data(int ac, char **av, int i);

//  ipc_bonus.c
void			init_philo_ipc(t_data *data, t_philo *philo);

//	philosopher_bonus.c
void			philosopher(t_data *data);

// philosopher_utils_bonus.c
void			grab_fork(t_philo *philo);

//	time_bonus.c
time_t			get_time_in_ms(void);
void			philo_sleep(time_t sleep_time);
void			sim_start_delay(time_t start_time);

//	output_bonus.c
void			write_status(t_philo *philo, bool reaper, t_status status);
void			print_status(t_philo *philo, char *str);

//	grim_reaper_bonus.c
void			*global_gluttony_reaper(void *_data);
void			*global_famine_reaper(void *_data);
void			*personal_grim_reaper(void *_data);
int				kill_all_philos(t_data *data, int exit_code);

//  utils_bonus.c
char			*ft_utoa(unsigned int nb, size_t len);
char			*ft_strcat(char	*dst, const char *src);
size_t			ft_strlen(const char *str);
void			unlink_global_sems(void);
bool			start_grim_reaper_threads(t_data *data);

//  cleanup_bonus.c
void			*free_data(t_data *data);
int				sem_error_cleanup(t_data *data);
int				data_cleanup(t_data *data, int exit_code);

//	exit_bonus.c
void			child_exit(t_data *data, int exit_code);
int				msg(char *str, char *detail, int exit_no);
int				error_failure(char *str, char *details, t_data *data);
void			*error_null(char *str, char *details, t_data *data);

#endif
