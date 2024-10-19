/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenasso <nbenasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:33:06 by ielhasso          #+#    #+#             */
/*   Updated: 2024/05/03 16:58:37 by nbenasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

static int	ft_error(int index, char *dir)
{
	if (index == 0)
		printf("minishell: cd: HOME not set\n");
	else if (index == 2)
		printf("minishell: cd: %s: %s\n", dir, strerror(errno));
	else
	{
		printf("cd: error retrieving current directory: getcwd:");
		printf(" cannot access parent directories:\
			No such file or directory\n");
	}
	return (1);
}

static char	*ft_get_home_path(char *dir, t_list *envp)
{
	t_env	*env;
	char	*home;

	home = NULL;
	if (dir != NULL)
		return (dir);
	while (envp != NULL)
	{
		env = envp->content;
		if (ft_strncmp(env->key, "HOME", 5) == 0)
			home = env->value;
		envp = envp->next;
	}
	return (home);
}

static void	ft_swap(t_list *envp, char **gpwd)
{
	char	**pwd;
	char	**oldpwd;
	t_env	*env;

	pwd = NULL;
	oldpwd = NULL;
	while (envp != NULL)
	{
		env = envp->content;
		if (ft_strncmp(env->key, "PWD", 4) == 0)
			pwd = &env->value;
		else if (ft_strncmp(env->key, "OLDPWD", 7) == 0)
			oldpwd = &env->value;
		envp = envp->next;
	}
	if (pwd != NULL && oldpwd != NULL)
	{
		free(*oldpwd);
		*oldpwd = *pwd;
		*pwd = ft_strjoin(*gpwd, "");
	}
}

static void	ft_change(char *str, char *dir, char **gpwd, t_list *envp)
{
	char	*tmp;
	char	*new_gpwd;

	if (str == NULL)
	{
		ft_error(3, NULL);
		tmp = ft_strjoin("/", dir);
		new_gpwd = ft_strjoin(*gpwd, tmp);
		free(*gpwd);
		*gpwd = new_gpwd;
		free(tmp);
	}
	else
	{
		free(*gpwd);
		*gpwd = str;
	}
	ft_swap(envp, gpwd);
}

int	ft_chdir(t_cmd *cmd, t_list *envp, char **path)
{
	int		i;
	char	*dir;
	char	*str;

	dir = ft_get_home_path(cmd->args[1], envp);
	if (dir == NULL)
		return (ft_error(0, NULL));
	i = chdir(dir);
	if (i == -1)
		return (ft_error(2, cmd->args[1]));
	str = getcwd(NULL, 0);
	ft_change(str, dir, path, envp);
	return (0);
}
