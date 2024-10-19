/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenasso <nbenasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:00:03 by nbenasso          #+#    #+#             */
/*   Updated: 2024/04/22 19:00:04 by nbenasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *ndl, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ndl[0] == '\0')
		return ((char *)hay);
	while (i < len && hay[i])
	{
		j = 0;
		while (hay[i + j] == ndl[j] && ndl[j] && hay[i + j] && i + j < len)
			j++;
		if (ndl[j] == '\0')
			return ((char *)hay + i);
		else
			i++;
	}
	return (0);
}
