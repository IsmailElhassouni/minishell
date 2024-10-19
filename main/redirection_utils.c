/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:20:13 by ielhasso          #+#    #+#             */
/*   Updated: 2024/05/17 19:44:53 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heider/minishell.h"

void	ft_dup2(int fd1, int fd2)
{
	int	i;

	i = dup2(fd1, fd2);
	if (i < 0)
	{
		perror("dup2");
		exit(0);
	}
}

int	output_redirect(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (fd == -1)
	{
		perror(file);
		return (1);
	}
	ft_dup2(fd, 1);
	close(fd);
	return (0);
}

int	append_redirect(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	if (fd == -1)
	{
		perror(file);
		return (1);
	}
	ft_dup2(fd, 1);
	close(fd);
	return (0);
}

int	input_redirect(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		g_exit_status = 1;
		return (1);
	}
	ft_dup2(fd, 0);
	close(fd);
	return (0);
}

int	my_redirect(t_list *redir)
{
	t_redir	*redi;

	while (redir != NULL)
	{
		redi = redir->content;
		if (redi->type == 'O' && output_redirect(redi->file))
			return (1);
		if (redi->type == 'A' && append_redirect(redi->file))
			return (1);
		if (redi->type == 'I' && input_redirect(redi->file))
			return (1);
		if (redi->type == 'H' && input_redirect("/tmp/file1"))
			return (1);
		redir = redir->next;
	}
	return (0);
}
