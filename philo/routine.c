/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:23:14 by aaghzal           #+#    #+#             */
/*   Updated: 2025/01/27 20:38:21 by aaghzal          ###   ########.fr       */
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
