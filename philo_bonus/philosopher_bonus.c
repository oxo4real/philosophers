/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:26:04 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/03 14:44:54 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philosopher_routine(t_philo *philo);
static void	eat_sleep_routine(t_philo *philo);
static void	lone_philo_routine(t_philo *philo);

void	philosopher(t_data *data)
{
	t_philo	*philo;

	philo = data->this_philo;
	if (philo->data->nb_philos == 1)
		lone_philo_routine(philo);
	init_philo_ipc(data, philo);
	if (philo->data->must_eat_count == 0)
	{
		sem_post(philo->sem_philo_full);
		child_exit(data, CHILD_EXIT_PHILO_FULL);
	}
	if (philo->data->time_to_die == 0)
	{
		sem_post(philo->sem_philo_dead);
		child_exit(data, CHILD_EXIT_PHILO_DEAD);
	}
	sem_wait(philo->sem_meal);
	philo->last_meal = philo->data->start_time;
	sem_post(philo->sem_meal);
	sim_start_delay(philo->data->start_time);
	philosopher_routine(philo);
}

static void	philosopher_routine(t_philo *philo)
{
	write_status(philo, false, THINKING);
	if (philo->id % 2)
		usleep(300);
	while (1)
	{
		eat_sleep_routine(philo);
		write_status(philo, false, THINKING);
	}
}

static void	lone_philo_routine(t_philo *philo)
{
	philo->sem_philo_full = sem_open(SEM_NAME_FULL, O_CREAT,
			S_IRUSR | S_IWUSR, philo->data->nb_philos);
	if (philo->sem_philo_full == SEM_FAILED)
		exit(CHILD_EXIT_ERR_SEM);
	sem_wait(philo->sem_philo_full);
	sim_start_delay(philo->data->start_time);
	if (philo->data->must_eat_count == 0)
	{
		sem_post(philo->sem_philo_full);
		exit(CHILD_EXIT_PHILO_FULL);
	}
	print_status(philo, "has taken a fork");
	philo_sleep(philo->data->time_to_die);
	print_status(philo, "died");
	free_data(philo->data);
	exit(CHILD_EXIT_PHILO_DEAD);
}

static void	eat_sleep_routine(t_philo *philo)
{
	grab_fork(philo);
	grab_fork(philo);
	write_status(philo, false, EATING);
	sem_wait(philo->sem_meal);
	philo->is_eating = false;
	philo->last_meal = get_time_in_ms();
	sem_post(philo->sem_meal);
	philo_sleep(philo->data->time_to_eat);
	sem_wait(philo->sem_meal);
	philo->is_eating = false;
	sem_post(philo->sem_meal);
	write_status(philo, false, SLEEPING);
	sem_post(philo->sem_forks);
	sem_post(philo->sem_forks);
	sem_wait(philo->sem_meal);
	philo->nb_forks_held -= 2;
	philo->times_ate += 1;
	sem_post(philo->sem_meal);
	philo_sleep(philo->data->time_to_sleep);
}
