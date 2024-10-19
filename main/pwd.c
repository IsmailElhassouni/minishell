/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:39:17 by ielhasso          #+#    #+#             */
/*   Updated: 2024/05/20 19:07:17 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

int	ft_pwd(char *gpwd)
{
	if (gpwd == NULL)
	{
		printf("error retrieving current directory: getcwd: cannot ");
		printf("access parent directories: No such file or directory\n");
	}
	else
		printf("%s\n", gpwd);
	return (0);
}

void	disable_echo(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

char	*expand_variables(char *line, t_list *envp)
{
	int		j;
	char	*expanded_line;

	j = 0;
	while (line[j])
	{
		if (line[j] == '$' && line[j + 1])
		{
			expanded_line = variable_expander(&line[j + 1], envp);
			free(line);
			line = expanded_line;
			break ;
		}
		j++;
	}
	return (line);
}

char	*no_file_error(char **paths, char *cmd, char *str2)
{
	if (!paths && access(str2, X_OK))
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		frees(paths);
		return (free(cmd), NULL);
	}
	return ((void *)1);
}
