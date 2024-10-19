/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_to_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:37:52 by nbenasso          #+#    #+#             */
/*   Updated: 2024/05/14 16:31:10 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

void	tab_to_space(char *str)
{
	int	q;

	q = 0;
	while (*str)
	{
		if (!q && (*str == '\'' || *str == '\"'))
			q = 1;
		else if (q && (*str == '\'' || *str == '\"'))
			q = 0;
		if (!q && *str == '\t')
		{
			*str = ' ';
		}
		str++;
	}
}

int	ft_valid_env_name_tow(char *value)
{
	int	i;

	i = 0;
	if (!ft_isalpha(value[0]) && value[0] != '_')
	{
		printf("minishell: '%s': not a valid identifier\n", value);
		g_exit_status = 1;
		return (0);
	}
	while (value[i] != 0)
	{
		if (value[i] != '_' && !ft_isalnum(value[i]))
		{
			printf("minishell: '%s': not a valid identifier\n", value);
			g_exit_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

void	frees(char **path)
{
	int	i;

	if (!path)
		return ;
	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}
