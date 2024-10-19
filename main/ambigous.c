/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambigous.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:33:06 by ielhasso          #+#    #+#             */
/*   Updated: 2024/05/20 19:02:05 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

static int	is_ambigous_var_valid(char *var, char *joined)
{
	if (ft_strchr(var, '"') || ft_strchr(var, '\''))
	{
		free(var);
		free(joined);
		return (0);
	}
	return (1);
}

static int	find_end_of_var(char *s, int i)
{
	if (ft_isdigit(s[i]))
		i++;
	else
		while (ft_isalnum(s[i]) || s[i] == '_')
			i++;
	return (i);
}

static int	ambigous_err_msg(char *expanded, char *joined, t_prs *prs, int i)
{
	if (!expanded || ft_strchr(expanded, ' '))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(joined, 2);
		ft_put_error(": ambiguous redirect");
		free(joined);
		prs->i = i;
		return (-1);
	}
	free(joined);
	free(expanded);
	return (0);
}

static char	*get_ambigous_var(char *joined, char *var)
{
	char	*temp;

	temp = NULL;
	temp = joined;
	joined = ft_strjoin(joined, "$");
	free(temp);
	temp = joined;
	joined = ft_strjoin(joined, var);
	free(temp);
	return (joined);
}

int	check_ambigous_redirect(char *s, t_list *env_lst, t_prs *prs,
		t_redir *redir)
{
	char	*var;
	char	*expanded;
	char	*joined;

	int (i), (j);
	if (redir->type == 'H')
		return (0);
	expanded = NULL;
	joined = NULL;
	i = prs->i;
	while (!expanded && s[i] == '$')
	{
		i++;
		j = i;
		i = find_end_of_var(s, i);
		var = ft_substr(s, j, i - j);
		if (!is_ambigous_var_valid(var, joined))
			return (0);
		joined = get_ambigous_var(joined, var);
		expanded = variable_expander(var, env_lst);
		free(var);
	}
	if (!ambigous_err_msg(expanded, joined, prs, i))
		return (0);
	return (-1);
}
