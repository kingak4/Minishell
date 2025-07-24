/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minipipe_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:43:29 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/24 01:43:31 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_child_pipe(int *pipefd, t_mini *mini)
{
	ft_close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	mini->pipe_read = pipefd[0];
	mini->pid = -1;
	mini->parent = 0;
}

void	setup_parent_pipe(int *pipefd, pid_t pid, t_mini *mini)
{
	ft_close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	mini->pipe_write = pipefd[1];
	mini->pid = pid;
	mini->last = 0;
}
