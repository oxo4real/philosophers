/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:17:51 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/02 18:55:34 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static char	*set_local_sem_name(const char *str, unsigned int id)
{
	unsigned int	i;
	unsigned int	digit_count;
	char			*sem_name;
	char			*tmp;

	digit_count = 0;
	i = id;
	while (i)
	{
		digit_count++;
		i /= 10;
	}
	i = ft_strlen(str) + digit_count;
	sem_name = malloc (sizeof * sem_name * (i + 1));
	if (sem_name == NULL)
		return (NULL);
	sem_name[0] = '\0';
	sem_name = ft_strcat(sem_name, str);
	tmp = ft_utoa(id, digit_count);
	sem_name = ft_strcat(sem_name, tmp);
	free(tmp);
	return (sem_name);
}

static bool	set_philo_sem_names(t_philo *philo)
{
	philo->sem_meal_name = set_local_sem_name(SEM_NAME_MEAL, philo->id + 1);
	if (philo->sem_meal_name == NULL)
		return (false);
	return (true);
}

static t_philo	**init_philosophers(t_data *data)
{
	t_philo			**philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philo) * (data->nb_philos + 1));
	if (!philos)
		return (error_null(STR_ERR_MALLOC, NULL, 0));
	i = 0;
	while (i < data->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (error_null(STR_ERR_MALLOC, NULL, 0));
		philos[i]->data = data;
		philos[i]->is_eating = false;
		philos[i]->id = i;
		if (!set_philo_sem_names(philos[i]))
			return (error_null(STR_ERR_MALLOC, NULL, data));
		philos[i]->times_ate = 0;
		philos[i]->nb_forks_held = 0;
		philos[i]->ate_enough = false;
		i++;
	}
	return (philos);
}

static bool	init_global_semaphores(t_data *data)
{
	unlink_global_sems();
	data->sem_forks = sem_open(SEM_NAME_FORKS, O_CREAT,
			S_IRUSR | S_IWUSR, data->nb_philos);
	if (data->sem_forks == SEM_FAILED)
		return (sem_error_cleanup(data));
	data->sem_write = sem_open(SEM_NAME_WRITE, O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (data->sem_write == SEM_FAILED)
		return (sem_error_cleanup(data));
	data->sem_philo_full = sem_open(SEM_NAME_FULL, O_CREAT,
			S_IRUSR | S_IWUSR, data->nb_philos);
	if (data->sem_philo_full == SEM_FAILED)
		return (sem_error_cleanup(data));
	data->sem_philo_dead = sem_open(SEM_NAME_DEAD, O_CREAT,
			S_IRUSR | S_IWUSR, data->nb_philos);
	if (data->sem_philo_dead == SEM_FAILED)
		return (sem_error_cleanup(data));
	data->sem_stop = sem_open(SEM_NAME_STOP, O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (data->sem_stop == SEM_FAILED)
		return (sem_error_cleanup(data));
	return (true);
}

t_data	*init_data(int ac, char **av, int i)
{
	t_data	*data;

	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (error_null(STR_ERR_MALLOC, NULL, 0));
	data->nb_philos = ft_atoi(av[i++]);
	data->time_to_die = ft_atoi(av[i++]);
	data->time_to_eat = ft_atoi(av[i++]);
	data->time_to_sleep = ft_atoi(av[i++]);
	data->must_eat_count = -1;
	data->philo_full_count = 0;
	data->stop_sim = false;
	if (ac - 1 == 5)
		data->must_eat_count = ft_atoi(av[i]);
	if (!init_global_semaphores(data))
		return (NULL);
	data->philos = init_philosophers(data);
	if (!data->philos)
		return (NULL);
	data->pids = malloc(sizeof * data->pids * data->nb_philos);
	if (!data->pids)
		return (error_null(STR_ERR_MALLOC, NULL, 0));
	return (data);
}
