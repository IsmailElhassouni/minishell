/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenasso <nbenasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:58:09 by nbenasso          #+#    #+#             */
/*   Updated: 2024/04/22 18:58:10 by nbenasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	size_t			i;
	unsigned char	*x;
	unsigned char	*y;

	x = src;
	y = dst;
	i = 0;
	if (src == dst)
		return (dst);
	if ((dst == NULL) && (src == NULL))
		return (NULL);
	while (i < n)
	{
		y[i] = x[i];
		i++;
	}
	return (y);
}
