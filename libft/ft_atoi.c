/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenasso <nbenasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:56:28 by nbenasso          #+#    #+#             */
/*   Updated: 2024/04/22 18:56:29 by nbenasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	a;
	int		b;
	int		c;

	a = 0;
	b = 0;
	c = 1;
	while (((*str <= 13) && (*str >= 9)) || (*str == 32))
		str++;
	while ((*str == '+') || (*str == '-'))
	{
		if (*str == '-')
			c = -1;
		b++;
		str++;
	}
	if (b > 1)
		return (0);
	while ((*str <= '9') && (*str >= '0'))
	{
		a = (*str - 48) + a * 10;
		str++;
	}
	return (a * c);
}
