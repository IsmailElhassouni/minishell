/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:37:52 by nbenasso          #+#    #+#             */
/*   Updated: 2024/05/16 19:26:20 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

void	close_pfds(int *pfds, int nbr)
{
	int	i;

	i = 0;
	while (i < 2 * nbr)
	{
		close(pfds[i]);
		i++;
	}
	free(pfds);
}

int	ft_valid_env_name(char *value)
{
	int	i;

	i = 0;
	if (!ft_isalpha(value[0]) && value[0] != '_')
	{
		printf("minishell: '%s': not a valid identifier\n", value);
		g_exit_status = 1;
		free(value);
		return (0);
	}
	while (value[i] != 0)
	{
		if (value[i] != '_' && !ft_isalnum(value[i]))
		{
			printf("minishell: '%s': not a valid identifier\n", value);
			g_exit_status = 1;
			free(value);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_unset(t_list **envp, char *value)
{
	t_env	*env;
	t_list	*pre;
	t_list	*current;

	pre = NULL;
	current = *envp;
	while (current != NULL)
	{
		env = current->content;
		if (ft_strncmp(env->key, value, ft_strlen(value) + 1) == 0)
		{
			if (pre != NULL)
				pre->next = current->next;
			else
			{
				*envp = current->next;
			}
			(free(env->key), free(env->value), free(env));
			free(current);
			return (0);
		}
		pre = current;
		current = current->next;
	}
	return (0);
}

int	ft_export(t_list **envpX, char *key, char *arg, t_list *tmp)
{
	char	*val;
	t_env	*env;
	t_list	*envp;

	if (!ft_valid_env_name(key))
		return (1);
	val = get_value(arg);
	tmp = *envpX;
	envp = *envpX;
	while (envp != NULL)
	{
		env = (envp)->content;
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0 && val != NULL)
			(free(env->value), env->value = val);
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return ((free(env->key), env->key = key), 0);
		tmp = envp;
		envp = (envp)->next;
	}
	env = env_in_node(key, val);
	if (!*envpX)
		*envpX = ft_lstnew(env);
	else
		tmp->next = ft_lstnew(env);
	return ((free(key), free(val)), 0);
}

int	spac(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}
