/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:41:02 by nbenasso          #+#    #+#             */
/*   Updated: 2024/05/20 18:08:04 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

int	ft_env(t_list *envX)
{
	t_env	*env;
	t_list	*envp;

	envp = envX;
	while (envp)
	{
		env = envp->content;
		if (env->value != NULL)
			printf("%s=%s\n", env->key, env->value);
		envp = envp->next;
	}
	return (0);
}

t_list	*defautl(t_env *tmp, t_list *env_lst, t_list *lst, char *s)
{
	tmp = env_in_node("PWD", s);
	free(s);
	lst = ft_lstnew(tmp);
	ft_lstadd_back(&env_lst, lst);
	tmp = env_in_node("SHLVL", "1");
	lst = ft_lstnew(tmp);
	ft_lstadd_back(&env_lst, lst);
	tmp = env_in_node("OLDPWD", NULL);
	lst = ft_lstnew(tmp);
	ft_lstadd_back(&env_lst, lst);
	tmp = env_in_node("_", "./minishell");
	lst = ft_lstnew(tmp);
	ft_lstadd_back(&env_lst, lst);
	return (env_lst);
}

void	free_env_list(t_list *env_cp)
{
	t_env	*temp;
	t_list	*next_node;

	while (env_cp != NULL)
	{
		next_node = env_cp->next;
		temp = env_cp->content;
		free(temp->key);
		free(temp->value);
		free(temp);
		free(env_cp);
		env_cp = next_node;
	}
}
