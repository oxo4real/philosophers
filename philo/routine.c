/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:23:14 by aaghzal           #+#    #+#             */
/*   Updated: 2025/01/28 09:44:34 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_one(t_philo *p);

void	*routine(void *philo)
{
	t_philo		*p;
	t_data		*d;

	p = (t_philo *)philo;
	d = p->data;
	if (d->philo_num == 1)
		return (handle_one(p), NULL);
	if (p->id % 2 != 0)
	{
		think(p);
		usleep(30);
	}
	while (true)
	{
		if (p->stop || d->stop)
			break ;
		eat(p);
		if (p->stop || d->stop)
			break ;
		rest(p);
		if (p->stop || d->stop)
			break ;
		think(p);
	}
	return (NULL);
}

void	handle_one(t_philo *p)
{
	take_a_fork(p);
	usleep(p->data->time_to_die * 1000);
	die(p);
}
