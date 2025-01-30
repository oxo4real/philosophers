/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:26:05 by aaghzal           #+#    #+#             */
/*   Updated: 2025/01/29 10:04:01 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(unsigned long long elapsed_time, t_philo *philo,
		char *action)
{
	// pthread_mutex_lock(&philo->data->print);
	// pthread_mutex_lock(&philo->data->death);
	pthread_mutex_lock(&philo->death);
	if (philo->stop || philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->print);
		// pthread_mutex_unlock(&philo->data->death);
		pthread_mutex_unlock(&philo->death);
		return ;
	}
	// pthread_mutex_unlock(&philo->data->death);
	pthread_mutex_unlock(&philo->death);
	ft_putnbr_fd(elapsed_time, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(action, 1);
	// pthread_mutex_unlock(&philo->data->print);
}
