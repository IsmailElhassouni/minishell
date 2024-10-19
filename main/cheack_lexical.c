/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheack_lexical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:41:02 by nbenasso          #+#    #+#             */
/*   Updated: 2024/05/20 18:59:26 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

int	ft_put_error(char *error)
{
	ft_putendl_fd(error, 2);
	return (1);
}

static int	check_pipe_errors(char *str)
{
	int	i;
	int	quote;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			quote = check_quote(str[i++], quote);
		if (str[i] == '|' && !quote)
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i] == '|')
				return (g_exit_status = 258, ft_put_error
					("minishell: syntax error near unexpected token `|'"));
		}
		i++;
		if (i >= (int)ft_strlen(str))
			break ;
	}
	return (0);
}

static int	pipe_and_endline(char *str)
{
	if (str == NULL)
		return (0);
	if (str[0] == '|')
	{
		if (str[1] == '|')
			return (ft_put_error
				("minishell: syntax error near unexpected token `||'"));
		else
			return (g_exit_status = 258, ft_put_error
				("minishell: syntax error near unexpected token `|'"));
	}
	else if (str[0] == ';')
	{
		if (str[1] == ';')
			return (g_exit_status = 258, ft_put_error
				("minishell: syntax error near unexpected token `;;'"));
		else
			return (g_exit_status = 258, ft_put_error
				("minishell: syntax error near unexpected token `;'"));
	}
	if (check_pipe_errors(str))
		return (1);
	return (0);
}

static int	check_quote_errors(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
			if (s[i] != '"')
				return (ft_put_error("minishell: unclosed double quote error"));
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (s[i] != '\'')
				return (ft_put_error("minishell: unclosed single quote error"));
		}
		i++;
	}
	return (0);
}

int	check_syntax_errors(char *input)
{
	char	*str;

	str = ft_strtrim(input, " ");
	if (pipe_and_endline(str) || check_quote_errors(str)
		|| check_redir_errors(str))
	{
		free(str);
		return (1);
	}
	if (str[ft_strlen(str) - 1] == '|')
	{
		free(str);
		g_exit_status = 258;
		return (ft_put_error
			("minishell: syntax error near unexpected token `newline'"));
	}
	free(str);
	return (0);
}
