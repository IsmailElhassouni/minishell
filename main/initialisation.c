/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:37:52 by nbenasso          #+#    #+#             */
/*   Updated: 2024/04/26 14:51:52 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

void	initialize_cmd_node(t_cmd *new, char *s, t_list *env_lst)
{
	int	i;

	i = 0;
	new->cmd = NULL;
	new->args = NULL;
	new->redir = NULL;
	allocate_args(s, new, env_lst);
}

void	init_env_node(t_env *new)
{
	new->key = NULL;
	new->value = NULL;
}

void	initialize_redir_node(t_redir *new)
{
	new->file = NULL;
	new->type = '\0';
}

void	initialize_prs_node(t_prs *prs)
{
	prs->i = 0;
	prs->arg_num = 0;
	prs->ambigous = 0;
	prs->ret_value = g_exit_status;
	prs->outside_quote = 0;
	prs->extra_args = NULL;
}
