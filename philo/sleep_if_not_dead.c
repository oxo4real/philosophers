/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_if_not_dead.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:37:25 by aaghzal           #+#    #+#             */
/*   Updated: 2025/01/28 18:40:13 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_if_not_dead(t_philo *p)
{
	pthread_mutex_lock(&p->death);
	pthread_mutex_lock(&p->data->death);
	if (!p->stop && !p->data->stop)
		usleep(p->data->time_to_eat * 1000);
	pthread_mutex_unlock(&p->death);
	pthread_mutex_unlock(&p->data->death);
}
