/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:29:03 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/06 15:30:02 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minipipe(t_mini *mini)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		mini->pipe_read = pipefd[0];
		mini->pid = -1;
		mini->parent = 0;
		return (2);
	}
	else
	{
		ft_close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		mini->pipe_write = pipefd[1];
		mini->pid = pid;
		mini->last = 0;
		return (1);
	}
}

void	redir_pipe(t_mini *mini, t_two *token, int type)
{
	int	flags;

	flags = O_CREAT | O_WRONLY | O_TRUNC;
	ft_close(mini->output_file);
	if (type == TRUNC)
		mini->output_file = open(token->str, flags, S_IRWXU);
	else
		mini->output_file = open(token->str, flags, S_IRWXU);
	if (mini->output_file == -1)
	{
		if (mini->pid == -1)
		{
			ft_putstr_fd("<< minishell: ", STDERR);
			ft_putstr_fd("no such file or directory:", STDERR);
			ft_putendl_fd(token->str, STDERR);
		}
		if (mini->pipe_write != -1 && type == TRUNC && mini->pipe_read != 1)
			mini->ret = 1;
		mini->no_file = 1;
		return ;
	}
	dup2(mini->output_file, STDOUT);
}

void	check_file_redirections_pipe(t_mini *mini, t_two *token)
{
	if (mini->no_file == 1)
		return ;
	while (token && token->next && mini->no_file != 1 && !is_type(token, PIPE))
	{
		if (is_type(token, TRUNC))
			redir_pipe(mini, token->next, TRUNC);
		if (is_type(token, APPEND))
			redir_pipe(mini, token->next, APPEND);
		if (is_type(token, INPUT) || is_type(token, INPUT_ECHO))
			input_pipe(mini, token->next);
		token = token->next;
	}
}

void	handle_pipe(t_mini *mini, t_two *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;

	pipe = 0;
	prev = find_prev_pipe(token, NOSKIP);
	next = find_next_pipe(token, NOSKIP);
	if (prev && is_type(prev, PIPE))
		pipe = minipipe(mini);
	if (next && pipe != 1 && mini->no_file != 1)
		handle_pipe(mini, next->next);
	if ((prev == NULL || is_type(prev, PIPE)) && pipe != 1)
	{
		if (mini->no_file != 1)
			process_pipe_segment(mini, prev, token);
	}
	return ;
}
