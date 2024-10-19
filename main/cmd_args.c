/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:37:52 by nbenasso          #+#    #+#             */
/*   Updated: 2024/04/26 15:02:11 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

static int	args_counter(char *s)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		if (s[i] == ' ')
		{
			while (s[i] == ' ')
				i++;
			ret++;
		}
		i++;
	}
	return (ret);
}

int	count_extra_args(char *s, int i, int j, t_list *env_lst)
{
	char	*temp;
	char	*tmp;
	int		ret;

	ret = 0;
	while (s[i])
	{
		while (s[i] && s[i] != '$')
			i++;
		if (s[i] == '$')
		{
			i++;
			j = i;
			while (s[i] && s[i] != ' ' && s[i] != '"' && s[i] != '\''
				&& s[i] != '$')
				i++;
			temp = ft_substr(s, j, i - j);
			tmp = variable_expander(temp, env_lst);
			free(temp);
			if (ft_strchr(tmp, ' '))
				ret += args_counter(tmp);
			free(tmp);
		}
	}
	return (ret);
}
