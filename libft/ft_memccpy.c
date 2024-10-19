/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenasso <nbenasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:57:57 by nbenasso          #+#    #+#             */
/*   Updated: 2024/04/22 18:57:58 by nbenasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*y;
	unsigned char	*x;

	y = (unsigned char *)src;
	x = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		if (y[i] == (unsigned char)c)
		{
			x[i] = y[i];
			return (&x[i + 1]);
		}
		x[i] = y[i];
		i++;
	}
	return (NULL);
}
