/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:37:52 by nbenasso          #+#    #+#             */
/*   Updated: 2024/05/20 18:53:52 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

static void	handle(char **args, t_list **cmd, t_list **envp)
{
	if (!ft_isdigit(args[1][0]))
	{
		printf("exit\nminishell: exit: %s:", args[1]);
		printf(" numeric argument required\n");
		free_env_list(*envp);
		free_cmds(*cmd);
		exit(255);
	}
}

static void	handel_tow(char **args, t_list **cmds, t_list **envp)
{
	if (args[1] == NULL)
	{
		printf("exit\n");
		free_env_list(*envp);
		free_cmds(*cmds);
		exit(g_exit_status);
	}
}

void	ft_exit(char **args, int i, t_list **cmds, t_list **envp)
{
	int (j);
	handel_tow(args, cmds, envp);
	if (args[2] == NULL)
	{
		i = ft_atoi(args[1]);
		j = 0;
		if (args[1][0] == '-' || args[1][0] == '+')
			j = 1;
		while (args[1][j] != '\0')
		{
			if (!ft_isdigit(args[1][j]))
			{
				printf("exit\nminishell: exit: %s:", args[1]);
				printf(" numeric argument required\n");
				(free_env_list(*envp), free_cmds(*cmds), exit(255));
			}
			j++;
		}
		printf("exit\n");
		(free_env_list(*envp), free_cmds(*cmds), exit(i));
	}
	else
		handle(args, cmds, envp);
	printf("exit\nminishell: exit: too many arguments\n");
	g_exit_status = 1;
}
