/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 08:29:17 by ielhasso          #+#    #+#             */
/*   Updated: 2024/05/16 18:55:31 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

static char	*get_keys(char *env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i] != '+' && env[i] != '=' && env[i] != '\0')
		i++;
	tmp = ft_substr(env, 0, i);
	return (tmp);
}

static int	append_env(char *value, t_list **envp, int is_found, char *key)
{
	t_list	*temp;
	char	*new_value;

	temp = *envp;
	while (temp)
	{
		if (ft_strncmp(((t_env *)temp->content)->key, key, ft_strlen(key)
				+ 1) == 0)
		{
			is_found = 1;
			break ;
		}
		temp = temp->next;
	}
	if (is_found)
	{
		new_value = ft_strjoin(((t_env *)temp->content)->value, value
				+ ft_strlen(key) + 2);
		free(((t_env *)temp->content)->value);
		((t_env *)temp->content)->value = new_value;
		return (free(key), 0);
	}
	else
		return (g_exit_status = ft_export(envp, key, value, NULL), 0);
}

int	chek_for_append(char *value, t_list **envp)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i + 1] && value[i] == '+' && value[i + 1] == '=')
		{
			g_exit_status = append_env(value, envp, 0, get_keys(value));
			return (0);
		}
		if (value[i] == '+' && value[i + 1] != '=')
		{
			printf("minishell: '%s': not a valid identifier\n", value);
			g_exit_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

void	set_env_value(t_env *env, char *arg, int nbr_cmds)
{
	if (nbr_cmds != 1)
	{
		free(env->value);
		env->value = ft_strdup("");
	}
	else if (ft_strcmp(arg, "env") == 0)
	{
		free(env->value);
		env->value = ft_strdup("/usr/bin/env");
	}
	else
	{
		free(env->value);
		env->value = ft_strdup(arg);
	}
}

void	set_(char **args, t_list **envpX, int nbr_cmds)
{
	int		i;
	t_list	*tmp;
	t_list	*envp;
	t_env	*env;
	t_list	*s;
	s = *envpX;
	tmp = NULL;
	envp = *envpX;
	i = 0;
	while (args[i])
		i++;
	while ((envp) != NULL && i > 0)
	{
		env = (envp)->content;
		if (!ft_strncmp(env->key, "_", ft_strlen("_") + 1) && args[i - 1])
		{
			set_env_value(env, args[i - 1], nbr_cmds);
			break ;
		}
		tmp = (envp);
		(envp) = (envp)->next;
	}
	if (envp == NULL && i > 0)
	{
		if_is_unset(args[i - 1], envpX, env);
	}
	*envpX = s;
}
