/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:05:25 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/07 10:55:25 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_size(char *s, int j);
static bool	check_only_spaces(char *s);
static bool	zero(char *s);
int			ft_atoi(char *str);

bool	is_valid_input(char **av)
{
	int		signe;
	int		i;
	int		j;

	j = 1;
	while (av[j])
	{
		signe = 1;
		i = 0;
		if (!av[j][i] || !check_size(av[j], j))
			return (false);
		while (av[j][i] == ' ')
			i++;
		while (av[j][i] == '+' || av[j][i] == '-')
		{
			if (av[j][i] == '-')
				signe *= -1;
			i++;
		}
		if (signe < 0 && !zero(&av[j][i]))
			return (false);
		j++;
	}
	return (true);
}

static bool	check_size(char *s, int j)
{
	int		size;
	char	*s1;

	size = 0;
	while (*s == ' ' || *s == '-' || *s == '+' || *s == '0')
		s++;
	s1 = s;
	while (*s >= '0' && *s <= '9')
	{
		s++;
		size++;
	}
	if (!check_only_spaces(s))
		return (false);
	if (((j == 1 && size == 3
				&& ft_strncmp(s1, "200", 3) > 0)
			|| (j == 1 && (size > 3 || size == 0)))
		|| ((j > 1 && size == 10
				&& ft_strncmp(s1, "2147483647", 10) > 0)
			|| size > 20)
		|| (j < 5 && size == 0))
		return (false);
	return (true);
}

static bool	check_only_spaces(char *s)
{
	while (*s)
	{
		if (*s != ' ')
			return (false);
		s++;
	}
	return (true);
}

static bool	zero(char *s)
{
	while (*s)
	{
		if (*s != '0' && *s != ' ')
			return (false);
		s++;
	}
	return (true);
}

int	ft_atoi(char *str)
{
	int	num;

	num = 0;
	while (*str <= ' ')
		str++;
	while (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - 48);
		str++;
	}
	return (num);
}
