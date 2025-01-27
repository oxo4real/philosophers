/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_max.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:17:03 by aaghzal           #+#    #+#             */
/*   Updated: 2025/01/27 16:18:00 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char	min(unsigned char a, unsigned char b)
{
	if (a < b)
		return (a);
	return (b);
}

unsigned char	max(unsigned char a, unsigned char b)
{
	if (a > b)
		return (a);
	return (b);
}
