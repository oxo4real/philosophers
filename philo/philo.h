/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:16:29 by aaghzal           #+#    #+#             */
/*   Updated: 2025/01/27 20:37:35 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

# define ULL_MAX "18446744073709551615"
# define USAGE "Usage:\t./philo number_of_philosophers \
time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"

typedef struct s_data
{
	unsigned char		philo_num;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	bool				meals;
	unsigned long long	meals_to_eat;
	bool				stop;
	unsigned long long	start_time;
	pthread_mutex_t		forks[200];
	pthread_mutex_t		print;
}				t_data;

typedef struct s_philo
{
	unsigned char		id;
	unsigned long long	last_eaten;
	bool				is_eating;
	unsigned long long	meals_eaten;
	bool				stop;
	t_data				*data;
}				t_philo;

int					ft_strncmp(const char *s1, const char *s2, int n);
int					ft_intcmp(char *w1, char *w2);
int					valid_input(char **av);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				*routine(void *phil);
void				ft_putnbr_fd(unsigned long long nb, int fd);
void				die(t_philo *philo);
void				take_a_fork(t_philo *philo);
void				eat(t_philo *philo);
void				think(t_philo *philo);
void				rest(t_philo *philo);
unsigned char		ft_atouc(char *str);
unsigned long long	ft_atoull(char *str);
unsigned char		min(unsigned char a, unsigned char b);
unsigned char		max(unsigned char a, unsigned char b);

#endif
