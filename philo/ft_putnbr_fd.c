/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:06:32 by aaghzal           #+#    #+#             */
/*   Updated: 2024/06/27 17:33:22 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putnbr_fd(unsigned long long nb, int fd)
{
	char			c;

	c = (nb % 10) + 48;
	if (nb / 10 != 0)
	{
		ft_putnbr_fd(nb / 10, fd);
	}
	ft_putchar_fd(c, fd);
}
