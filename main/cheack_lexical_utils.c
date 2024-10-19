/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheack_lexical_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:41:02 by nbenasso          #+#    #+#             */
/*   Updated: 2024/04/26 15:05:38 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

int	check_quote(char c, int quote)
{
	if (c == '"' && quote == 0)
		quote = 2;
	else if (c == '\'' && quote == 0)
		quote = 1;
	else if ((c == '"' && quote == 2) || (c == '\'' && quote == 1))
		quote = 0;
	return (quote);
}
