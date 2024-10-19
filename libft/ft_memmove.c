/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenasso <nbenasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:58:15 by nbenasso          #+#    #+#             */
/*   Updated: 2024/04/22 18:58:16 by nbenasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_move(char *b, char *a, size_t len)
{
	size_t	i;

	if (a >= b)
	{
		i = 0;
		while (i < len)
		{
			b[i] = a[i];
			i++;
		}
	}
	else
	{
		i = len;
		while (i > 0)
		{
			b[i - 1] = a[i - 1];
			i--;
		}
	}
	return (b);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*a;
	char	*b;

	a = (char *)src;
	b = (char *)dst;
	if (src == dst)
		return (dst);
	return (ft_move(b, a, len));
}
