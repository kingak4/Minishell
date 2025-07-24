/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:20:47 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/24 01:20:56 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_pipe(t_mini *mini, t_two *token)
{
	int	fd;

	if (mini->pipe_read != -1)
		ft_close(mini->pipe_read);
	fd = open(token->str, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: no such file or directory: ", STDERR);
		ft_putendl_fd(token->str, STDERR);
		mini->no_file = 1;
		return ;
	}
	dup2(fd, STDIN_FILENO);
	mini->pipe_read = fd;
}

void	redir_pipe(t_mini *mini, t_two *token, int type)
{
	int	flags;

	flags = O_CREAT | O_WRONLY;
	if (type == TRUNC)
		flags |= O_TRUNC;
	else if (type == APPEND)
		flags |= O_APPEND;
	ft_close(mini->output_file);
	mini->output_file = open(token->str, flags, 0644);
	if (mini->output_file == -1)
	{
		if (mini->pid == -1)
		{
			ft_putstr_fd("<< minishell: ", STDERR);
			ft_putstr_fd("no such file or directory: ", STDERR);
			ft_putendl_fd(token->str, STDERR);
		}
		if (mini->pipe_write != -1 && type == TRUNC && mini->pipe_read != 1)
			mini->ret = 1;
		mini->no_file = 1;
		return ;
	}
	dup2(mini->output_file, STDOUT_FILENO);
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
