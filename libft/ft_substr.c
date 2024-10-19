/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenasso <nbenasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:00:17 by nbenasso          #+#    #+#             */
/*   Updated: 2024/04/22 19:00:18 by nbenasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_smallest(const char *s, unsigned int start, size_t len)
{
	if (len > ft_strlen(s + start))
		return (ft_strlen(s + start) + 1);
	return (len + 1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*x;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	i = 0;
	x = (char *)malloc(sizeof(char) * ft_smallest(s, start, len));
	if (x == 0)
		return (NULL);
	while (i < (ft_smallest(s, start, len) - 1))
	{
		x[i] = s[i + start];
		i++;
	}
	x[i] = '\0';
	return (x);
}
