/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:32:15 by ielhasso          #+#    #+#             */
/*   Updated: 2024/05/18 13:29:32 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

static void	get_file_quote(t_redir *redir, char *s, t_list *env_lst, t_prs *prs)
{
	char	*temp;
	char	*tmp;

	if (s[prs->i] == '"')
	{
		temp = double_quotes(s, env_lst, prs);
		tmp = redir->file;
		redir->file = ft_strjoin(redir->file, temp);
		free(temp);
		free(tmp);
		if (redir->file == NULL)
			redir->file = ft_strdup("");
	}
	if (s[prs->i] == '\'')
	{
		temp = single_quotes(s, prs);
		tmp = redir->file;
		redir->file = ft_strjoin(redir->file, temp);
		free(temp);
		free(tmp);
	}
}

static void	join_filepath(t_redir *redir, char *s, t_list *env_lst, t_prs *prs)
{
	char	*temp;
	char	*tmp;
	int		j;

	j = prs->i;
	if (s[prs->i] && s[prs->i] != '"' && s[prs->i] != '\'' && s[prs->i] != '>'
		&& s[prs->i] != '<')
	{
		while (s[prs->i] && s[prs->i] != ' ' && s[prs->i] != '<'
			&& s[prs->i] != '>' && s[prs->i] != '"' && s[prs->i] != '\'')
			prs->i++;
		temp = ft_substr(s, j, prs->i - j);
		tmp = env_var_checker(temp, env_lst, prs);
		free(temp);
		temp = redir->file;
		redir->file = ft_strjoin(redir->file, tmp);
		free(tmp);
		free(temp);
	}
}

void	get_filepath(t_redir *redir, char *s, t_list *env_lst, t_prs *prs)
{
	while (s[prs->i] == ' ')
		prs->i++;
	if (s[prs->i] == '$')
		if (check_ambigous_redirect(s, env_lst, prs, redir) == -1)
			prs->ambigous = 1;
	while (s[prs->i])
	{
		join_filepath(redir, s, env_lst, prs);
		get_file_quote(redir, s, env_lst, prs);
		if (!s[prs->i] || s[prs->i] == ' ' || s[prs->i] == '>'
			|| s[prs->i] == '<')
			break ;
	}
	while (s[prs->i] == ' ')
		prs->i++;
}

void	wait_cmds(int nbr_cmds)
{
	int	i;

	i = 0;
	while (i < nbr_cmds)
	{
		wait(NULL);
		i++;
	}
}
