/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:39:31 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/03 10:24:04 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	start_simulation(t_data *data);
static void	stop_simulation(t_data *data);

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
	stop_simulation(data);
	return (EXIT_SUCCESS);
}

static bool	start_simulation(t_data *data)
{
	unsigned int	i;

	data->start_time = get_time_in_ms() + (data->nb_philos * 20);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&data->philos[i]->thread, NULL,
				&philosopher, data->philos[i]) != 0)
			return (error_failure(STR_ERR_THREAD, NULL, data));
		i++;
	}
	if (data->nb_philos > 1)
	{
		if (pthread_create(&data->grim_reaper, NULL,
				&grim_reaper, data) != 0)
			return (error_failure(STR_ERR_THREAD, NULL, data));
	}
	return (true);
}

static void	stop_simulation(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philos[i]->thread, NULL);
		i++;
	}
	if (data->nb_philos > 1)
		pthread_join(data->grim_reaper, NULL);
	destroy_mutexes(data);
	free_data(data);
}
