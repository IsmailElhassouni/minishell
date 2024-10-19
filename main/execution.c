/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:37:52 by nbenasso          #+#    #+#             */
/*   Updated: 2024/05/20 18:54:10 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

int	*create_pipes(int nbr_pipes)
{
	int	*pfds;
	int	i;
	int	j;

	pfds = malloc(2 * nbr_pipes * sizeof(int));
	i = 0;
	while (i < nbr_pipes)
	{
		j = pipe(pfds + 2 * i);
		if (j < 0)
		{
			perror("pipe: ");
			exit(0);
		}
		i++;
	}
	return (pfds);
}

void	exec_cmd(t_list *cmds, int *pfds, t_list *envp, int i)
{
	int		nbr_pipes;
	char	*cmd_path;
	char	**tab;
	t_cmd	*cmd;

	cmd_path = NULL;
	tab = list_to_arr(envp);
	nbr_pipes = ft_lstsize(cmds) + i / 2 - 1;
	if (cmds->next)
		ft_dup2(pfds[i + 1], 1);
	if (i != 0)
		ft_dup2(pfds[i - 2], 0);
	close_pfds(pfds, nbr_pipes);
	cmd = cmds->content;
	if (my_redirect(cmd->redir))
		exit(1);
	if (exec_cmdd(cmds, cmd, &envp, is_cmd(cmd)))
		exit(g_exit_status);
	cmd_path = get_cmd_path(cmd->cmd, get_paths(envp));
	ft_execve(cmd_path, cmd->args, tab);
}

int	create_childs(t_list *cmds, int *pfds, t_list *envp)
{
	int	i;
	int	pid;

	pid = 0;
	i = 0;
	while (cmds)
	{
		pid = fork();
		if (pid == 0)
			exec_cmd(cmds, pfds, envp, i);
		cmds = cmds->next;
		i += 2;
	}
	return (pid);
}

static void	ft_set_exit_status(int nbr_cmds)
{
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
	{
		if (WTERMSIG(g_exit_status) == SIGQUIT)
			write(1, "Quit: 3\n", 8);
		g_exit_status = 128 + WTERMSIG(g_exit_status);
	}
	wait_cmds(nbr_cmds);
}

int	my_exec(t_list *cmds, t_list **envp, t_cmd *cmd)
{
	int (nbr_cmds), (pid), (*pfds);
	pfds = NULL;
	nbr_cmds = ft_lstsize(cmds);
	if (ft_heredoc(cmds, *envp))
		return (1);
	if (nbr_cmds > 0)
	{
		cmd = cmds->content;
		pid = is_cmd(cmds->content);
		set_(cmd->args, envp, nbr_cmds);
		if (nbr_cmds == 1 && pid != 0)
			ft_cmd(cmds, cmds->content, envp, pid);
		else
		{
			if (nbr_cmds > 1)
				pfds = create_pipes(nbr_cmds - 1);
			pid = create_childs(cmds, pfds, *envp);
			if (nbr_cmds > 1)
				close_pfds(pfds, nbr_cmds - 1);
			waitpid(pid, &g_exit_status, 0);
			ft_set_exit_status(nbr_cmds);
		}
	}
	return (1);
}
