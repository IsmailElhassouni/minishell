/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:20:59 by ielhasso          #+#    #+#             */
/*   Updated: 2024/04/26 14:54:07 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

char	*remove_spaces(char *s)
{
	char	*res;
	char	*temp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (res == NULL)
		return (NULL);
	temp = s;
	s = ft_strtrim(s, " ");
	free(temp);
	while (s[i])
	{
		if (s[i] == ' ' && s[i + 1] == ' ')
			i++;
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	free(s);
	return (res);
}

void	fill_arg(char *temp, t_cmd *new, t_list *env_lst, t_prs *prs)
{
	char	*tmp;

	tmp = env_var_checker(temp, env_lst, prs);
	free(temp);
	temp = new->args[prs->arg_num];
	new->args[prs->arg_num] = ft_strjoin(new->args[prs->arg_num], tmp);
	free(temp);
	free(tmp);
}
