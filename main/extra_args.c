/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:03:27 by ielhasso          #+#    #+#             */
/*   Updated: 2024/04/19 17:22:07 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

void	add_extra_args(t_cmd *new, t_prs *prs)
{
	int	i;

	i = 1;
	while (prs->extra_args[i])
	{
		new->args[prs->arg_num + i] = prs->extra_args[i];
		i++;
	}
	i = 1;
	while (prs->extra_args[i])
	{
		prs->arg_num++;
		i++;
	}
	free(prs->extra_args);
	prs->extra_args = NULL;
}
