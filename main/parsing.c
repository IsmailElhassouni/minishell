/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:39:17 by ielhasso          #+#    #+#             */
/*   Updated: 2024/05/13 18:33:26 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

static char	*change_pipe(char *s)
{
	int		i;
	int		single_quote_open;
	int		double_quote_open;
	char	*temp;

	single_quote_open = 0;
	double_quote_open = 0;
	temp = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			single_quote_open = !single_quote_open;
		else if (s[i] == '"')
			double_quote_open = !double_quote_open;
		if (s[i] == '|' && !single_quote_open && !double_quote_open)
			temp[i++] = -124;
		temp[i] = s[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

t_list	*split_pipe(t_list *head, char *input, t_list *env_lst)
{
	char	**commands;
	t_cmd	*temp;
	t_list	*new;
	int		i;

	i = 0;
	input = change_pipe(input);
	commands = ft_split(input, -124);
	while (commands[i])
	{
		temp = new_node(commands[i], env_lst);
		new = ft_lstnew(temp);
		ft_lstadd_back(&head, new);
		i++;
	}
	i = 0;
	if (commands)
	{
		while (commands[i])
			free(commands[i++]);
		free(commands);
	}
	free(input);
	return (head);
}
