/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenasso <nbenasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:59:27 by nbenasso          #+#    #+#             */
/*   Updated: 2024/04/22 18:59:28 by nbenasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	str;

	i = 0;
	str = c;
	if (s == NULL)
		return (NULL);
	while (s[i] && s[i] != str)
		i++;
	if (s[i] == str)
		return ((char *)&s[i]);
	return (NULL);
}
