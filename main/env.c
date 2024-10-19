/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:41:02 by nbenasso          #+#    #+#             */
/*   Updated: 2024/05/15 20:15:55 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

char	*get_key(char *env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i] != '=' && env[i] != '\0')
		i++;
	tmp = ft_substr(env, 0, i);
	return (tmp);
}

char	*get_value(char *env)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (env[i] != '=' && env[i])
		i++;
	if (env[i] == '=')
		tmp = ft_substr(env, i + 1, ft_strlen(env) - i);
	return (tmp);
}

char	*inc_shell_level(char *value)
{
	char	*tmp;

	tmp = value;
	value = ft_itoa(ft_atoi(value) + 1);
	free(tmp);
	return (value);
}

t_env	*env_in_node(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	init_env_node(new);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	return (new);
}

t_list	*env_copy(t_list *env_lst, char **env, char *s)
{
	int		i;
	char	*key;
	char	*value;
	t_list	*lst;
	t_env	*tmp;

	s = getcwd(NULL, 0);
	i = 0;
	if (*env == NULL)
		return (defautl(NULL, env_lst, NULL, s));
	while (env[i])
	{
		key = get_key(env[i]);
		value = get_value(env[i]);
		if (!ft_strcmp(key, "SHLVL"))
			value = inc_shell_level(value);
		tmp = env_in_node(key, value);
		lst = ft_lstnew(tmp);
		ft_lstadd_back(&env_lst, lst);
		free(key);
		free(value);
		i++;
	}
	free(s);
	return (env_lst);
}
