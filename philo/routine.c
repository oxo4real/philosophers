/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:23:14 by aaghzal           #+#    #+#             */
/*   Updated: 2025/01/27 17:49:25 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	t_philo		*p;
	t_data		*d;

	p = (t_philo *)philo;
	d = p->data;
	if (p->id % 2 != 0)
	{
		think(p);
		usleep(30);
	}
	while (true)
	{
		if (d->stop || (d->meals && p->meals_eaten >= d->meals_to_eat))
			break ;
		eat(p);
		if (d->stop || (d->meals && p->meals_eaten >= d->meals_to_eat))
			break ;
		rest(p);
		if (d->stop)
			break ;
		think(p);
	}
	if (!d->stop)
		die(p);
	return (NULL);
}
