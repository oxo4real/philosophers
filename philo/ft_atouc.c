/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atouc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:32:55 by aaghzal           #+#    #+#             */
/*   Updated: 2025/01/14 12:51:57 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char	ft_atouc(char *str)
{
	unsigned char	num;

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
