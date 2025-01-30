/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:53:06 by aaghzal           #+#    #+#             */
/*   Updated: 2025/01/29 15:11:48 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	rest(t_philo *philo)
{
	struct timeval		time;
	unsigned long long	curr_time;
	unsigned long long	elapsed_time;

	pthread_mutex_lock(&philo->data->print);
	gettimeofday(&time, NULL);
	curr_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	elapsed_time = curr_time - philo->data->start_time;
	print_action(elapsed_time, philo, "is sleeping\n");
	pthread_mutex_unlock(&philo->data->print);
	usleep(philo->data->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	struct timeval		time;
	unsigned long long	curr_time;
	unsigned long long	elapsed_time;

	pthread_mutex_lock(&philo->data->print);
	gettimeofday(&time, NULL);
	curr_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	elapsed_time = curr_time - philo->data->start_time;
	print_action(elapsed_time, philo, "is thinking\n");
	pthread_mutex_unlock(&philo->data->print);
}

void	take_a_fork(t_philo *philo)
{
	struct timeval		time;
	unsigned long long	curr_time;
	unsigned long long	elapsed_time;

	pthread_mutex_lock(&philo->data->print);
	gettimeofday(&time, NULL);
	curr_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	elapsed_time = curr_time - philo->data->start_time;
	print_action(elapsed_time, philo, "has taken a fork\n");
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
	pthread_mutex_lock(&p->data->print);
	// pthread_mutex_lock(&p->access);
	p->is_eating = true;
	// pthread_mutex_unlock(&p->access);
	gettimeofday(&time, NULL);
	elapsed = time.tv_sec * 1000 + time.tv_usec / 1000 - p->data->start_time;
	print_action(elapsed, p, "is eating\n");
	sleep_if_not_dead(p);
	pthread_mutex_unlock(&p->data->forks[max(p->id % n, (p->id + 1) % n)]);
	pthread_mutex_unlock(&p->data->forks[min(p->id % n, (p->id + 1) % n)]);
	gettimeofday(&time, NULL);
	// pthread_mutex_lock(&p->access);
	p->last_eaten = time.tv_sec * 1000 + time.tv_usec / 1000;
	p->is_eating = false;
	p->meals_eaten++;
	pthread_mutex_unlock(&p->data->print);
	// pthread_mutex_unlock(&p->access);
}

void	die(t_philo *philo)
{
	struct timeval		time;
	unsigned long long	curr_time;
	unsigned long long	elapsed_time;

	pthread_mutex_lock(&philo->data->print);
	gettimeofday(&time, NULL);
	curr_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	elapsed_time = curr_time - philo->data->start_time;
	ft_putnbr_fd(elapsed_time, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd("died\n", 1);
	pthread_mutex_unlock(&philo->data->print);
}
