/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:17:09 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/02 18:00:45 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*free_data(t_data *data)
{
	unsigned int	i;

	if (!data)
		return (NULL);
	if (data->philos != NULL)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			if (data->philos[i] != NULL)
			{
				if (data->philos[i]->sem_meal_name)
					free(data->philos[i]->sem_meal_name);
				free(data->philos[i]);
			}
			i++;
		}
		free(data->philos);
	}
	if (data->pids)
		free(data->pids);
	free(data);
	return (NULL);
}

int	sem_error_cleanup(t_data *data)
{
	sem_close(data->sem_forks);
	sem_close(data->sem_write);
	sem_close(data->sem_philo_full);
	sem_close(data->sem_philo_dead);
	sem_close(data->sem_stop);
	unlink_global_sems();
	return (error_failure(STR_ERR_SEM, NULL, data));
}

int	data_cleanup(t_data *data, int exit_code)
{
	if (data != NULL)
	{
		pthread_join(data->famine_reaper, NULL);
		pthread_join(data->gluttony_reaper, NULL);
		sem_close(data->sem_forks);
		sem_close(data->sem_write);
		sem_close(data->sem_philo_full);
		sem_close(data->sem_philo_dead);
		sem_close(data->sem_stop);
		unlink_global_sems();
		free_data(data);
	}
	return (exit_code);
}
