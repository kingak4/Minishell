/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:21:18 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/24 01:43:06 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_pipe_segment(t_mini *mini, t_two *prev, t_two *token)
{
	(void)prev;
	execute(&token, mini);
}

int	minipipe(t_mini *mini)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		setup_child_pipe(pipefd, mini);
		return (2);
	}
	setup_parent_pipe(pipefd, pid, mini);
	return (1);
}
