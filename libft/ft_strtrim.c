/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenasso <nbenasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:00:13 by nbenasso          #+#    #+#             */
/*   Updated: 2024/04/22 19:00:14 by nbenasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_end(char const *s1, char const *set)
{
	int	i;
	int	b;

	i = ft_strlen(s1);
	i--;
	while (i > 0)
	{
		b = 0;
		while ((s1[i] != set[b]) && set[b])
			b++;
		if (s1[i] == set[b])
			i--;
		else
			break ;
	}
	return (i);
}

static int	ft_start(char const *s1, char const *set)
{
	int	i;
	int	b;

	i = 0;
	while (s1[i])
	{
		b = 0;
		while ((s1[i] != set[b]) && set[b])
			b++;
		if (s1[i] == set[b])
			i++;
		else
			break ;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		lstart;
	int		lend;
	int		i;
	char	*b;

	if (s1 == NULL || set == NULL)
		return (NULL);
	lstart = ft_start(s1, set);
	if (s1[lstart] == '\0')
		return (ft_substr(s1, 0, 0));
	lend = ft_end(s1, set);
	i = (lend - lstart) + 1;
	b = ft_substr(s1, lstart, i);
	return (b);
}
