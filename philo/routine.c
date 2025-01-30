/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:23:14 by aaghzal           #+#    #+#             */
/*   Updated: 2025/01/29 10:01:31 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_one(t_philo *p);
int		check_if_dead(t_philo *p, t_data *d);

void	*routine(void *philo)
{
	t_philo	*p;
	t_data	*d;

	p = (t_philo *)philo;
	d = p->data;
	if (d->philo_num == 1)
		return (handle_one(p), NULL);
	if (p->id % 2 != 0)
	{
		think(p);
		usleep(100);
	}
	while (true)
	{
		eat(p);
		if (check_if_dead(p, d))
			return (NULL);
		rest(p);
		if (check_if_dead(p, d))
			return (NULL);
		think(p);
		if (check_if_dead(p, d))
			return (NULL);
	}
}

int	check_if_dead(t_philo *p, t_data *d)
{
	pthread_mutex_lock(&p->death);
	// pthread_mutex_lock(&d->death);
	if (p->stop || d->stop)
	{
		pthread_mutex_unlock(&p->death);
		// pthread_mutex_unlock(&d->death);
		return (1);
	}
	pthread_mutex_unlock(&p->death);
	// pthread_mutex_unlock(&d->death);
	return (0);
}

void	handle_one(t_philo *p)
{
	take_a_fork(p);
	usleep(p->data->time_to_die * 1000);
	die(p);
}
