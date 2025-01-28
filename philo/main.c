/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:16:10 by aaghzal           #+#    #+#             */
/*   Updated: 2025/01/28 18:25:39 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_data(char **av, t_data *data);
static void	init_philo(t_philo *philo, t_data *data);
static void	join_threads(pthread_t *threads, unsigned char amount);
static void	creat_threads(pthread_t *threads, t_philo *philo,
				unsigned char amount);

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		philo[200];
	pthread_t	threads[200];

	if (ac < 5 || ac > 6)
		return (ft_putstr_fd(USAGE, 2), 1);
	if (!valid_input(av))
		return (ft_putstr_fd("Invalid input\n", 2), 1);
	init_data(av, &data);
	init_philo(philo, &data);
	creat_threads(threads, philo, data.philo_num);
	if (data.philo_num > 1)
		azrael(philo, &data);
	join_threads(threads, data.philo_num);
	while (data.philo_num--)
	{
		pthread_mutex_destroy(&philo[data.philo_num].access);
		pthread_mutex_destroy(&philo[data.philo_num].death);
		pthread_mutex_destroy(&data.forks[data.philo_num]);
	}
	pthread_mutex_destroy(&data.print);
	pthread_mutex_destroy(&data.death);
}

static void	init_data(char **av, t_data *data)
{
	struct timeval	time;
	int				i;

	data->philo_num = ft_atouc(av[1]);
	data->time_to_die = ft_atoull(av[2]);
	data->time_to_eat = ft_atoull(av[3]);
	data->time_to_sleep = ft_atoull(av[4]);
	data->meals = false;
	if (av[5])
	{
		data->meals = true;
		data->meals_to_eat = ft_atoull(av[5]);
	}
	data->stop = false;
	gettimeofday(&time, NULL);
	data->start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->death, NULL);
}

static void	init_philo(t_philo *philo, t_data *data)
{
	unsigned char	i;

	i = 0;
	while (i < data->philo_num)
	{
		philo[i].id = i + 1;
		philo[i].last_eaten = data->start_time;
		philo[i].is_eating = false;
		philo[i].meals_eaten = 0;
		philo[i].stop = false;
		philo[i].data = data;
		pthread_mutex_init(&philo[i].access, NULL);
		pthread_mutex_init(&philo[i].death, NULL);
		i++;
	}
}

static void	creat_threads(pthread_t *threads, t_philo *philo,
		unsigned char amount)
{
	unsigned char	i;

	i = 0;
	while (i < amount)
	{
		pthread_create(&threads[i], NULL, routine, &philo[i]);
		i++;
	}
}

static void	join_threads(pthread_t *threads, unsigned char amount)
{
	unsigned char	i;

	i = 0;
	while (i < amount)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
