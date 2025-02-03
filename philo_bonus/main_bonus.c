/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:18:35 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/03 12:43:11 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool		has_simulation_stopped(t_data *data);
static bool	start_simulation(t_data *data);
static int	get_child_philo(t_data *data, pid_t *pid);
static int	stop_simulation(t_data	*data);

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (ac - 1 < 4 || ac - 1 > 5)
		return (msg(STR_USAGE, NULL, EXIT_FAILURE));
	if (!is_valid_input(av))
		return (msg("Invalid input\n", NULL, EXIT_FAILURE));
	data = init_data(ac, av, 1);
	if (!data)
		return (EXIT_FAILURE);
	if (!start_simulation(data))
		return (EXIT_FAILURE);
	if (stop_simulation(data) == -1)
		return (data_cleanup(data, EXIT_FAILURE));
	return (data_cleanup(data, EXIT_SUCCESS));
}

bool	has_simulation_stopped(t_data *data)
{
	bool	ret;

	sem_wait(data->sem_stop);
	ret = data->stop_sim;
	sem_post(data->sem_stop);
	return (ret);
}

static bool	start_simulation(t_data *data)
{
	unsigned int	i;
	pid_t			pid;

	data->start_time = get_time_in_ms() + (data->nb_philos * 20);
	i = -1;
	while (++i < data->nb_philos)
	{
		pid = fork();
		if (pid == -1)
			return (error_failure(STR_ERR_FORK, NULL, data));
		else if (pid > 0)
			data->pids[i] = pid;
		else if (pid == 0)
		{
			data->this_philo = data->philos[i];
			philosopher(data);
		}
	}
	if (start_grim_reaper_threads(data) == false)
		return (false);
	return (true);
}

static int	get_child_philo(t_data *data, pid_t *pid)
{
	int	philo_exit_code;
	int	exit_code;

	if (*pid && waitpid(*pid, &philo_exit_code, WNOHANG) != 0)
	{
		if (WIFEXITED(philo_exit_code))
		{
			exit_code = WEXITSTATUS(philo_exit_code);
			if (exit_code == CHILD_EXIT_PHILO_DEAD)
				return (kill_all_philos(data, 1));
			if (exit_code == CHILD_EXIT_ERR_PTHREAD
				|| exit_code == CHILD_EXIT_ERR_SEM)
				return (kill_all_philos(data, -1));
			if (exit_code == CHILD_EXIT_PHILO_FULL)
			{
				data->philo_full_count += 1;
				return (1);
			}
		}
	}
	return (0);
}

static int	stop_simulation(t_data	*data)
{
	unsigned int	i;
	int				exit_code;

	sim_start_delay(data->start_time);
	while (has_simulation_stopped(data) == false)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			exit_code = get_child_philo(data, &data->pids[i]);
			if (exit_code == 1 || exit_code == -1)
			{
				sem_wait(data->sem_stop);
				data->stop_sim = true;
				sem_post(data->sem_philo_full);
				sem_post(data->sem_philo_dead);
				sem_post(data->sem_stop);
				return (exit_code);
			}
			i++;
		}
	}
	return (0);
}
