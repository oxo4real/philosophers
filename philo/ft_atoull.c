/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoull.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:34:15 by aaghzal           #+#    #+#             */
/*   Updated: 2025/01/14 12:52:35 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned long long	ft_atoull(char *str)
{
	unsigned long long	num;

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
