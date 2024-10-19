/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:41:02 by nbenasso          #+#    #+#             */
/*   Updated: 2024/05/16 19:23:12 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

static int	ignore_n(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i] != NULL && argv[i][0] == '-' && argv[i][1] == 'n')
	{
		j = 1;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

int	ft_echo(char **argv)
{
	int	i;
	int	j;

	j = 0;
	if (argv[0] != NULL)
	{
		j = ignore_n(argv);
		i = j;
		while (argv[i] != NULL)
		{
			write(1, argv[i], ft_strlen(argv[i]));
			i++;
			if (argv[i] != NULL)
				write(1, " ", 1);
		}
	}
	if (j == 0)
		write(1, "\n", 1);
	return (0);
}
