/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:24:29 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/02 17:24:33 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	grab_fork(t_philo *philo)
{
	sem_wait(philo->sem_forks);
	sem_wait(philo->sem_meal);
	if (philo->nb_forks_held <= 0)
		write_status(philo, false, GOT_FORK_1);
	if (philo->nb_forks_held == 1)
		write_status(philo, false, GOT_FORK_2);
	philo->nb_forks_held += 1;
	sem_post(philo->sem_meal);
}
