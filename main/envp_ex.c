/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:11:25 by ielhasso          #+#    #+#             */
/*   Updated: 2024/05/14 16:10:13 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

static void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	envp_sort(char **tab, int size)
{
	int		len;
	int		wall;
	int		current;
	char	*pivot;

	if (size < 2)
		return (0);
	wall = 0;
	current = 0;
	pivot = tab[size - 1];
	len = ft_strlen(pivot);
	while (current < size)
	{
		if (ft_strncmp(tab[current], pivot, len) <= 0)
		{
			if (current != wall)
				ft_swap(&tab[current], &tab[wall]);
			wall++;
		}
		current++;
	}
	envp_sort(tab, wall - 1);
	envp_sort(tab + wall - 1, size - wall + 1);
	return (0);
}

static char	*ft_join(t_env *env)
{
	char	*tab;
	char	*tmp;

	if (env->value != NULL)
	{
		tmp = ft_strjoin(env->key, "=");
		tab = ft_strjoin(tmp, env->value);
		free(tmp);
		return (tab);
	}
	return (env->key);
}

char	**list_to_arr(t_list *lst)
{
	int		i;
	int		size;
	char	**tab;
	t_env	*env;

	size = ft_lstsize(lst) + 1;
	tab = malloc(size * sizeof(char *));
	i = 0;
	while (i < size - 1)
	{
		env = lst->content;
		tab[i] = ft_join(env);
		lst = lst->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int	ft_display_envp(t_list *envp, int i, int j)
{
	char	**tab;

	tab = list_to_arr(envp);
	envp_sort(tab, ft_lstsize(envp) + 1);
	while (tab[i] != NULL)
	{
		if (ft_strncmp(tab[i], "_=", 2) != 0)
		{
			ft_putstr_fd("declare -x ", 1);
			j = 0;
			while (tab[i][j] != '=' && tab[i][j] != '\0')
			{
				ft_putchar_fd(tab[i][j], 1);
				j++;
			}
			if (tab[i][j] != '\0')
				(printf("=\"%s\"\n", &tab[i][j + 1]), free(tab[i]));
			else
				ft_putchar_fd('\n', 1);
		}
		else
			free(tab[i]);
		i++;
	}
	return (free(tab), 0);
}
