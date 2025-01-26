/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:53:06 by aaghzal           #+#    #+#             */
/*   Updated: 2025/01/26 20:31:38 by aaghzal          ###   ########.fr       */
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
	ft_putnbr_fd(elapsed_time, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" is sleeping\n", 1);
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
	ft_putnbr_fd(elapsed_time, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" is thinking\n", 1);
}

void	eat(t_philo *philo)
{
	struct timeval		time;
	unsigned long long	curr_time;
	unsigned long long	elapsed_time;

	gettimeofday(&time, NULL);
	curr_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	elapsed_time = curr_time - philo->data->start_time;
	ft_putnbr_fd(elapsed_time, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" is eating\n", 1);
	usleep(philo->data->time_to_eat * 1000);
}

void	take_a_fork(t_philo *philo)
{
	struct timeval		time;
	unsigned long long	curr_time;
	unsigned long long	elapsed_time;

	gettimeofday(&time, NULL);
	curr_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	elapsed_time = curr_time - philo->data->start_time;
	ft_putnbr_fd(elapsed_time, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" has taken a fork\n", 1);
}

void	die(t_philo *philo)
{
	struct timeval		time;
	unsigned long long	curr_time;
	unsigned long long	elapsed_time;

	gettimeofday(&time, NULL);
	curr_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	elapsed_time = curr_time - philo->data->start_time;
	ft_putnbr_fd(elapsed_time, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" died\n", 1);
}
