/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:39:17 by ielhasso          #+#    #+#             */
/*   Updated: 2024/05/13 15:09:11 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

void	ft_execve(char *path, char **args, char **tab)
{
	if (path)
	{
		execve(path, args, tab);
		perror("minishell");
		exit(127);
	}
	exit(127);
}

static char	*get_envp(t_list *envp, char *key)
{
	t_env	*env;

	while (envp != NULL)
	{
		env = envp->content;
		if (ft_strcmp(key, env->key) == 0)
			return (env->value);
		envp = envp->next;
	}
	return (NULL);
}

char	**get_paths(t_list *envp)
{
	char	**paths;
	char	*path;

	path = get_envp(envp, "PATH");
	if (path != NULL)
	{
		paths = ft_split(path, ':');
		return (paths);
	}
	return (NULL);
}

static char	*ft_local_cmd(char *str, char *cmd)
{
	if (access(str, X_OK) == 0)
		return (str);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (free(cmd), NULL);
}

char	*get_cmd_path(char *cmd, char **paths)
{
	int		i;
	char	*str;
	char	*str2;

	if (!cmd)
		exit(0);
	str2 = cmd;
	if (cmd[0] == '.' || cmd[0] == '/')
		return (cmd);
	if (cmd[0] != '\0' && paths != NULL)
	{
		cmd = ft_strjoin("/", cmd);
		i = 0;
		while (paths[i] != NULL)
		{
			str = ft_strjoin(paths[i], cmd);
			if (access(str, F_OK | X_OK) == 0)
				return (frees(paths), free(cmd), str);
			free(str);
			i++;
		}
	}
	if (!no_file_error(paths, cmd, str2))
		return (NULL);
	return (frees(paths), ft_local_cmd(str2, cmd));
}
