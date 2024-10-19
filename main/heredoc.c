/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:32:15 by ielhasso          #+#    #+#             */
/*   Updated: 2024/05/20 18:52:22 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

static void	ft_here_sig(int signal)
{
	if (signal == SIGINT)
		exit(1);
}

static void	ft_child_sig(int signal)
{
	if (signal == SIGINT)
		printf("\n");
}

static void	ft_here(char *limiter, t_list *envp, t_list *cmd)
{
	char	*line;

	int (i), (fd);
	fd = open("/tmp/file1", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ft_here_sig);
		line = readline(">");
		if (line == NULL)
			exit(0);
		line = expand_variables(line, envp);
		if (line)
		{
			i = ft_strncmp(line, limiter, ft_strlen(limiter) + 1);
			if (i == 0)
				break ;
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
	(free(line), close(fd));
	(free_cmds(cmd), free_env_list(envp));
	exit(0);
}

static int	ft_exec_heredoc(t_redir *rec, t_list *envp, t_list *cmd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		ft_here(rec->file, envp, cmd);
	waitpid(pid, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	return (g_exit_status);
}

int	ft_heredoc(t_list *cmds, t_list *envp)
{
	t_cmd	*cmd;
	t_list	*red;
	t_redir	*rec;

	signal(SIGQUIT, &ft_child_sig);
	signal(SIGINT, &ft_child_sig);
	while (cmds)
	{
		cmd = cmds->content;
		red = cmd->redir;
		while (red != NULL)
		{
			rec = red->content;
			if (rec->type == 'H')
			{
				if (ft_exec_heredoc(rec, envp, cmds) == 1)
					return (1);
			}
			red = red->next;
		}
		cmds = cmds->next;
	}
	return (0);
}
