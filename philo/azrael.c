/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   azrael.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:30:20 by aaghzal           #+#    #+#             */
/*   Updated: 2025/01/28 11:01:10 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	get_tm(void);
void				kill_philo(t_philo *p, t_data *d);

void	azrael(t_philo *p, t_data *d)
{
	int				i;
	int				not_done;

	while (true)
	{
		i = -1;
		not_done = 0;
		while (++i < d->philo_num)
		{
			if (d->meals && !p[i].stop && p[i].meals_eaten < d->meals_to_eat)
				not_done++;
			if (get_tm() - p[i].last_eaten > d->time_to_die
				&& !p[i].is_eating && !p[i].stop)
			{
				kill_philo(&p[i], d);
				if (!d->meals)
					return ;
			}
		}
		if (d->meals && not_done == 0)
		{
			d->stop = true;
			return ;
		}
	}
}

unsigned long long	get_tm(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	kill_philo(t_philo *p, t_data *d)
{
	p->stop = true;
	die(p);
	if (!d->meals)
		d->stop = true;
}
