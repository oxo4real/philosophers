/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   azrael.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:30:20 by aaghzal           #+#    #+#             */
/*   Updated: 2025/01/27 20:46:30 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	azrael(t_philo *philo, t_data *data)
{
	int		i;
	int		not_done;

	while (true)
	{
		i = 0;
		not_done = 0;
		while (i < data->philo_num)
		{
			if (data->meals && philo[i].meals_eaten < data->meals_to_eat)
				not_done++;
			...
		}
	}
}
