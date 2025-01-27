/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:53:06 by aaghzal           #+#    #+#             */
/*   Updated: 2025/01/27 17:48:38 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	rest(t_philo *philo)
{
	struct timeval		time;
	unsigned long long	curr_time;
	unsigned long long	elapsed_time;

	gettimeofday(&time, NULL);
	curr_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	elapsed_time = curr_time - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print);
	ft_putnbr_fd(elapsed_time, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" is sleeping\n", 1);
	pthread_mutex_unlock(&philo->data->print);
	usleep(philo->data->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	struct timeval		time;
	unsigned long long	curr_time;
	unsigned long long	elapsed_time;

	gettimeofday(&time, NULL);
	curr_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	elapsed_time = curr_time - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print);
	ft_putnbr_fd(elapsed_time, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" is thinking\n", 1);
	pthread_mutex_unlock(&philo->data->print);
}

void	take_a_fork(t_philo *philo)
{
	struct timeval		time;
	unsigned long long	curr_time;
	unsigned long long	elapsed_time;

	gettimeofday(&time, NULL);
	curr_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	elapsed_time = curr_time - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print);
	ft_putnbr_fd(elapsed_time, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" has taken a fork\n", 1);
	pthread_mutex_unlock(&philo->data->print);
}

void	eat(t_philo *p)
{
	struct timeval		time;
	unsigned long long	elapsed;
	unsigned char		n;

	n = p->data->philo_num;
	pthread_mutex_lock(&p->data->forks[min(p->id % n, (p->id + 1) % n)]);
	take_a_fork(p);
	pthread_mutex_lock(&p->data->forks[max(p->id % n, (p->id + 1) % n)]);
	take_a_fork(p);
	p->is_eating = true;
	gettimeofday(&time, NULL);
	elapsed = time.tv_sec * 1000 + time.tv_usec / 1000 - p->data->start_time;
	pthread_mutex_lock(&p->data->print);
	ft_putnbr_fd(elapsed, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(p->id, 1);
	ft_putstr_fd(" is eating\n", 1);
	pthread_mutex_unlock(&p->data->print);
	usleep(p->data->time_to_eat * 1000);
	p->is_eating = false;
	pthread_mutex_unlock(&p->data->forks[max(p->id % n, (p->id + 1) % n)]);
	pthread_mutex_unlock(&p->data->forks[min(p->id % n, (p->id + 1) % n)]);
	gettimeofday(&time, NULL);
	p->last_eaten = time.tv_sec * 1000 + time.tv_usec / 1000;
	p->meals_eaten++;
}

void	die(t_philo *philo)
{
	struct timeval		time;
	unsigned long long	curr_time;
	unsigned long long	elapsed_time;

	gettimeofday(&time, NULL);
	curr_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	elapsed_time = curr_time - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print);
	ft_putnbr_fd(elapsed_time, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" died\n", 1);
	pthread_mutex_unlock(&philo->data->print);
}
