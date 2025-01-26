/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:48:59 by aaghzal           #+#    #+#             */
/*   Updated: 2025/01/26 12:28:58 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_size(char *s, int j);
static int	check_only_spaces(char *s);
static int	zero(char *s);

int	valid_input(char **av)
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
			return (0);
		while (av[j][i] == ' ')
			i++;
		while (av[j][i] == '+' || av[j][i] == '-')
		{
			if (av[j][i] == '-')
				signe *= -1;
			i++;
		}
		if (signe < 0 && !zero(&av[j][i]))
			return (0);
		j++;
	}
	return (1);
}

static int	check_size(char *s, int j)
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
		return (0);
	if (((j == 1 && size == 3
				&& ft_strncmp(s1, "200", 3) > 0)
			|| (j == 1 && (size > 3 || size == 0)))
		|| ((j > 1 && size == 20
				&& ft_strncmp(s1, ULL_MAX, 20) > 0)
			|| size > 20))
		return (0);
	return (1);
}

static int	check_only_spaces(char *s)
{
	while (*s)
	{
		if (*s != ' ')
			return (0);
		s++;
	}
	return (1);
}

static int	zero(char *s)
{
	while (*s)
	{
		if (*s != '0' && *s != ' ')
			return (0);
		s++;
	}
	return (1);
}
