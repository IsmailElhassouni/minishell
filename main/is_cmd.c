/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:37:52 by nbenasso          #+#    #+#             */
/*   Updated: 2024/05/16 19:41:41 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

int	is_cmd(t_cmd *cmd)
{
	if (cmd->cmd == NULL)
		return (0);
	if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		return (2);
	else if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		return (3);
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		return (4);
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		return (5);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		return (6);
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
		return (7);
	return (0);
}

static int	exec_un_ex(t_cmd *cmd, t_list **envp, int status, int i)
{
	char	*key;

	if (status == 6)
	{
		while (cmd->args[i] != NULL && ft_valid_env_name_tow(cmd->args[i]))
		{
			g_exit_status = ft_unset(envp, cmd->args[i]);
			i++;
		}
	}
	else if (status == 7)
	{
		if (cmd->args[1] == NULL)
			g_exit_status = ft_display_envp(*envp, 0, 0);
		while (cmd->args[i] != NULL)
		{
			if (chek_for_append(cmd->args[i], envp))
			{
				key = get_key(cmd->args[i]);
				g_exit_status = ft_export(envp, key, cmd->args[i], NULL);
			}
			i++;
		}
	}
	return (0);
}

int	exec_cmdd(t_list *cmds, t_cmd *cmd, t_list **envp, int status)
{
	static char	*gpwd;

	if (gpwd == NULL && (status == 1 || status == 2))
		gpwd = getcwd(NULL, 0);
	if (status == 1)
		g_exit_status = ft_chdir(cmd, *envp, &gpwd);
	if (status == 2)
		g_exit_status = ft_pwd(gpwd);
	else if (status == 3)
		g_exit_status = ft_echo(cmd->args + 1);
	else if (status == 4)
		g_exit_status = ft_env(*envp);
	else if (status == 5)
		ft_exit(cmd->args, 0, &cmds, envp);
	else if (status == 6 || status == 7)
		exec_un_ex(cmd, envp, status, 1);
	else
		return (0);
	return (1);
}

int	ft_cmd(t_list *cmds, t_cmd *cmd, t_list **envp, int status)
{
	int	input;
	int	output;
	int	i;

	i = 0;
	if (cmd->redir != NULL)
	{
		input = dup(0);
		output = dup(1);
		i = my_redirect(cmd->redir);
	}
	if (i == 0)
		exec_cmdd(cmds, cmd, envp, status);
	if (cmd->redir != NULL)
	{
		ft_dup2(input, 0);
		ft_dup2(output, 1);
		close(input);
		close(output);
	}
	return (0);
}
