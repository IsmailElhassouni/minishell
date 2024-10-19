/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:37:52 by nbenasso          #+#    #+#             */
/*   Updated: 2024/05/20 18:07:18 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

static void	free_redirect(t_list *redir)
{
	t_list	*redir_temp;
	t_redir	*temp;

	while (redir != NULL)
	{
		redir_temp = redir;
		temp = redir->content;
		if (temp->file)
			free(temp->file);
		free(temp);
		redir = redir->next;
		free(redir_temp);
	}
}

void	sig_int(int signal)
{
	disable_echo();
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_exit_status = 1;
	}
}

static char	*ft_read_input(char *input, t_list *env_cp)
{
	input = readline("minishell$ ");
	if (input == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		free_env_list(env_cp);
		exit(g_exit_status);
	}
	if (ft_strcmp(input, ""))
		add_history(input);
	return (input);
}

void	free_cmds(t_list *cmd)
{
	t_list	*list_temp;
	t_cmd	*temp;
	int		i;

	i = 0;
	while (cmd != NULL)
	{
		list_temp = cmd;
		temp = cmd->content;
		if (temp->args)
		{
			i = 0;
			while (temp->args[i])
				free(temp->args[i++]);
			free(temp->args);
		}
		if (temp->redir)
			free_redirect(temp->redir);
		free(temp);
		cmd = cmd->next;
		free(list_temp);
	}
}

int	main(void)
{
	extern char	**environ;
	t_list		*env_cp;
	t_list		*cmds;
	char		*input;

	input = NULL;
	env_cp = env_copy(NULL, environ, NULL);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &sig_int);
		cmds = NULL;
		input = ft_read_input(input, env_cp);
		tab_to_space(input);
		if (input != NULL && spac(input) && !check_syntax_errors(input))
		{
			cmds = split_pipe(cmds, input, env_cp);
			my_exec(cmds, &env_cp, NULL);
		}
		free(input);
		free_cmds(cmds);
	}
	return (0);
}
