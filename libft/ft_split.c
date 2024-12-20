/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenasso <nbenasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:59:23 by nbenasso          #+#    #+#             */
/*   Updated: 2024/04/22 18:59:24 by nbenasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	count(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			count++;
		s++;
	}
	return (count);
}

static char	*ft_word_splitter(char *d, char *f)
{
	char	*p;
	size_t	i;

	p = (char *)malloc(f - d + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (d != f)
	{
		p[i] = *d;
		d++;
		i++;
	}
	p[i] = '\0';
	return (p);
}

static void	freeall(int i, char **p)
{
	int	j;

	j = -1;
	while (j++ <= i)
		free(p[j]);
	free(p);
}

char	**ft_split(char const *s, char v)
{
	char	**p;
	char	*f;
	size_t	i;

	p = (char **)malloc(sizeof(char *) * (count(s, v) + 1));
	if (s == NULL || !p)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		while (*s == v)
			s++;
		f = (char *)s;
		while (*f != v && *f != '\0')
			f++;
		if (s == f)
			break ;
		p[i] = ft_word_splitter((char *)s, f);
		if (!p[i])
			freeall(i, p);
		s = f;
		i++;
	}
	p[i] = NULL;
	return (p);
}
