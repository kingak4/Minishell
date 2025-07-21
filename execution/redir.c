/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:23:40 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/16 17:54:13 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirections(t_redirect *redir)
{
	if (!redir)
		return (1);
	if (redir->in == 1)
	{
		int fd = open(redir->file, O_RDONLY);
		if (fd == -1)
		{
			perror("open <");
			return (0);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (redir->out == 1)
	{
		int fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open >");
			return (0);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (redir->out == 2)
	{
		int fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("open >>");
			return (0);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (1);
}
