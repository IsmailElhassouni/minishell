/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:51:32 by ielhasso          #+#    #+#             */
/*   Updated: 2024/05/16 19:03:00 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

static int	skip_space_and_redir(char *s, int i)
{
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	while (s[i] == '>' || s[i] == '<')
	{
		i++;
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		while (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
			i++;
	}
	return (i);
}

int	check_for_quote(char c, int quote)
{
	if (c == '"' && quote == 0)
		quote = 2;
	else if (c == '\'' && quote == 0)
		quote = 1;
	else if ((c == '"' && quote == 2) || (c == '\'' && quote == 1))
		quote = 0;
	return (quote);
}

int	get_size(char *s)
{
	int	i;
	int	quote;
	int	ret;

	ret = 0;
	quote = 0;
	i = 0;
	while (s[i])
	{
		i = skip_space_and_redir(s, i);
		if (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
		{
			while ((s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
				|| (s[i] == ' ' && quote) || ((s[i] == '>' || s[i] == '<')
					&& quote))
				quote = check_for_quote(s[i++], quote);
			ret++;
		}
	}
	return (ret);
}

void	allocate_args(char *s, t_cmd *cmd, t_list *env_lst)
{
	int	ret;
	int	i;

	ret = get_size(s);
	if (ft_strchr(s, '$'))
		ret += count_extra_args(s, 0, 0, env_lst);
	cmd->args = malloc(sizeof(char *) * (ret + 1));
	i = 0;
	while (i <= ret)
		cmd->args[i++] = NULL;
}

void	if_is_unset(char *args, t_list **envp, t_env *env)
{
	if (ft_strcmp(args, "env") == 0)
	{
		env = env_in_node("_", "/usr/bin/env");
		(*envp) = ft_lstnew(env);
		return ;
	}
	env = env_in_node("_", args);
	(*envp) = ft_lstnew(env);
}
