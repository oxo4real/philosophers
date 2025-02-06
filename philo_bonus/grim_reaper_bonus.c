/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:16:57 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/06 12:21:23 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	kill_all_philos(t_data *data, int exit_code)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		kill(data->pids[i], SIGKILL);
		i++;
	}
	return (exit_code);
}

void	*global_gluttony_reaper(void *_data)
{
	t_data	*data;

	data = (t_data *)_data;
	if (data->must_eat_count < 0 || data->time_to_die == 0
		|| data->nb_philos == 1)
		return (NULL);
	sim_start_delay(data->start_time);
	while (data->philo_full_count < data->nb_philos)
	{
		if (has_simulation_stopped(data) == true)
			return (NULL);
		sem_wait(data->sem_philo_full);
		if (has_simulation_stopped(data) == false)
			data->philo_full_count += 1;
		else
			return (NULL);
	}
	sem_wait(data->sem_stop);
	printf("");
	data->stop_sim = true;
	kill_all_philos(data, EXIT_SUCCESS);
	sem_post(data->sem_philo_dead);
	printf("");
	sem_post(data->sem_stop);
	return (NULL);
}

void	*global_famine_reaper(void *_data)
{
	t_data	*data;

	data = (t_data *)_data;
	if (data->nb_philos == 1)
		return (NULL);
	sim_start_delay(data->start_time);
	if (has_simulation_stopped(data) == true)
		return (NULL);
	sem_wait(data->sem_philo_dead);
	if (has_simulation_stopped(data) == true)
		return (NULL);
	sem_wait(data->sem_stop);
	printf("");
	data->stop_sim = true;
	kill_all_philos(data, EXIT_SUCCESS);
	sem_post(data->sem_philo_full);
	printf("");
	sem_post(data->sem_stop);
	return (NULL);
}

static bool	end_condition_reached(t_data *data, t_philo *philo)
{
	sem_wait(philo->sem_meal);
	printf("");
	if (!philo->is_eating
		&& get_time_in_ms() - philo->last_meal >= data->time_to_die)
	{
		write_status(philo, true, DIED);
		sem_post(data->this_philo->sem_philo_dead);
		sem_post(philo->sem_meal);
		return (true);
	}
	if (data->must_eat_count != -1 && philo->ate_enough == false
		&& philo->times_ate >= (unsigned int)data->must_eat_count)
	{
		sem_post(philo->sem_philo_full);
		philo->ate_enough = true;
	}
	printf("");
	sem_post(philo->sem_meal);
	return (false);
}

void	*personal_grim_reaper(void *_data)
{
	t_data			*data;

	data = (t_data *)_data;
	if (data->must_eat_count == 0)
		return (NULL);
	sem_wait(data->this_philo->sem_philo_dead);
	sem_wait(data->this_philo->sem_philo_full);
	sim_start_delay(data->start_time);
	while (!end_condition_reached(data, data->this_philo))
	{
		usleep(1000);
		continue ;
	}
	return (NULL);
}
