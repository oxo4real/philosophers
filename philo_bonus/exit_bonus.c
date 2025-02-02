/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:17:30 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/02 18:00:55 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	msg(char *str, char *detail, int exit_no)
{
	if (!detail)
		printf(str, STR_PROG_NAME);
	else
		printf(str, STR_PROG_NAME, detail);
	return (exit_no);
}

int	error_failure(char *str, char *details, t_data *data)
{
	if (data != NULL)
		free_data(data);
	return (msg(str, details, 0));
}

void	*error_null(char *str, char *details, t_data *data)
{
	if (data != NULL)
		free_data(data);
	msg(str, details, EXIT_FAILURE);
	return (NULL);
}

void	child_exit(t_data *data, int exit_code)
{
	sem_post(data->this_philo->sem_meal);
	pthread_join(data->this_philo->personal_grim_reaper, NULL);
	if (exit_code == CHILD_EXIT_ERR_SEM)
		msg(STR_ERR_SEM, NULL, 0);
	if (exit_code == CHILD_EXIT_ERR_PTHREAD)
		msg(STR_ERR_THREAD, NULL, 0);
	sem_close(data->this_philo->sem_forks);
	sem_close(data->this_philo->sem_philo_full);
	sem_close(data->this_philo->sem_philo_dead);
	sem_close(data->this_philo->sem_write);
	sem_close(data->this_philo->sem_meal);
	free_data(data);
	exit(exit_code);
}
