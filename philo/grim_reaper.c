/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:05:03 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/03 10:41:09 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	end_condition_reached(t_data *data);
static void	set_sim_stop_flag(t_data *data, bool state);
static bool	kill_philo(t_philo *philo);
bool		has_simulation_stopped(t_data *data);

void	*grim_reaper(void *_data)
{
	t_data			*data;

	data = (t_data *)_data;
	if (data->must_eat_count == 0)
		return (NULL);
	set_sim_stop_flag(data, false);
	sim_start_delay(data->start_time);
	while (true)
	{
		if (end_condition_reached(data) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

static bool	end_condition_reached(t_data *data)
{
	unsigned int	i;
	bool			all_ate_enough;

	all_ate_enough = true;
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->philos[i]->meal_time_lock);
		if (kill_philo(data->philos[i]))
			return (true);
		if (data->must_eat_count != -1)
			if (data->philos[i]->times_ate
				< (unsigned int)data->must_eat_count)
				all_ate_enough = false;
		pthread_mutex_unlock(&data->philos[i]->meal_time_lock);
		i++;
	}
	if (data->must_eat_count != -1 && all_ate_enough == true)
	{
		set_sim_stop_flag(data, true);
		return (true);
	}
	return (false);
}

static bool	kill_philo(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if (!philo->is_eating
		&& (time - philo->last_meal) >= philo->data->time_to_die)
	{
		set_sim_stop_flag(philo->data, true);
		write_status(philo, true, DIED);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (true);
	}
	return (false);
}

static void	set_sim_stop_flag(t_data *data, bool state)
{
	pthread_mutex_lock(&data->sim_stop_lock);
	data->sim_stop = state;
	pthread_mutex_unlock(&data->sim_stop_lock);
}

bool	has_simulation_stopped(t_data *data)
{
	bool	r;

	r = false;
	pthread_mutex_lock(&data->sim_stop_lock);
	if (data->sim_stop == true)
		r = true;
	pthread_mutex_unlock(&data->sim_stop_lock);
	return (r);
}
