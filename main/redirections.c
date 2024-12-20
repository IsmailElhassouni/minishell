/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:20:13 by ielhasso          #+#    #+#             */
/*   Updated: 2024/04/26 14:39:26 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

char	*double_quotes(char *s, t_list *env_lst, t_prs *prs)
{
	int		j;
	char	*file;
	char	*temp;

	prs->i++;
	j = prs->i;
	while (s[prs->i] && s[prs->i] != '"')
		prs->i++;
	temp = ft_substr(s, j, prs->i - j);
	file = env_var_checker(temp, env_lst, prs);
	free(temp);
	prs->i++;
	return (file);
}

char	*single_quotes(char *s, t_prs *prs)
{
	int		j;
	char	*file;

	prs->i++;
	j = prs->i;
	while (s[prs->i] && s[prs->i] != '\'')
		prs->i++;
	file = ft_substr(s, j, prs->i - j);
	prs->i++;
	return (file);
}

static char	get_redir_type(char first, char second)
{
	if (first == '>' && second != '>')
		return ('O');
	else if (first == '<' && second != '<')
		return ('I');
	else if (first == '>' && second == '>')
		return ('A');
	else if (first == '<' && second == '<')
		return ('H');
	return (0);
}

static t_redir	*new_redirection_node(char *s, t_list *env_lst, t_prs *prs)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	initialize_redir_node(new);
	while (s[prs->i] == ' ')
		prs->i++;
	new->type = get_redir_type(s[prs->i], s[prs->i + 1]);
	if (new->type == 'O' || new->type == 'I')
	{
		prs->i++;
		get_filepath(new, s, env_lst, prs);
	}
	else
	{
		prs->i += 2;
		get_filepath(new, s, env_lst, prs);
	}
	return (new);
}

t_list	*redirections(t_list *redir, char *s, t_list *env_lst, t_prs *prs)
{
	t_list	*new;
	t_redir	*temp;

	while (s[prs->i])
	{
		if (s[prs->i] && s[prs->i] != '>' && s[prs->i] != '<')
			break ;
		temp = new_redirection_node(s, env_lst, prs);
		new = ft_lstnew(temp);
		ft_lstadd_back(&redir, new);
	}
	return (redir);
}
