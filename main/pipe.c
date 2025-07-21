/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:29:03 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/21 01:35:56 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

int	is_type(t_two *token, int type)
{
	if (!token)
		return (0);
	if (type == PIPE)
		return (token->str && ft_strcmp(token->str, "|") == 0);
	if (!token->redirect)
		return (0);
	if (type == TRUNC)
		return (token->redirect->out == 1);
	if (type == APPEND)
		return (token->redirect->out == 2);
	if (type == INPUT)
		return (token->redirect->in == 1);
	if (type == INPUT_ECHO)
		return (token->redirect->in == 2);
	return (0);
}

t_two *find_prev_pipe(t_two *token, int skip)
{
    t_two *curr = token;
    while (curr)
    {
        if (is_type(curr, PIPE))
        {
            if (skip == 0)
                return curr;
            skip--;
        }
        curr = curr->next;
    }
    return NULL;
}
t_two *find_next_pipe(t_two *token, int skip)
{
    t_two *curr = token;
    while (curr)
    {
        if (is_type(curr, PIPE))
        {
            if (skip == 0)
                return curr;
            skip--;
        }
        curr = curr->next;
    }
    return NULL;
}
void process_pipe_segment(t_mini *mini, t_two *prev, t_two *token)
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
		ft_close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		mini->pipe_read = pipefd[0];
		mini->pid = -1;
		mini->parent = 0;
		return (2);
	}
	else
	{
		ft_close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		mini->pipe_write = pipefd[1];
		mini->pid = pid;
		mini->last = 0;
		return (1);
	}
}

void input_pipe(t_mini *mini, t_two *token)
{
    int fd;

    // Zamykamy poprzedni plik wejściowy jeśli otwarty
    if (mini->pipe_read != -1)
        ft_close(mini->pipe_read);

    // Otwieramy plik do odczytu
    fd = open(token->str, O_RDONLY);
    if (fd == -1)
    {
        ft_putstr_fd("minishell: no such file or directory: ", STDERR);
        ft_putendl_fd(token->str, STDERR);
        mini->no_file = 1;
        return;
    }
    // Duplikujemy deskryptor pliku na stdin
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
	while (token && token->next && mini->no_file != 1
		&& !is_type(token, PIPE))
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
	t_two	*prev;
	t_two	*next;
	int		pipe;

	pipe = 0;
	prev = find_prev_pipe(token, 0);
	next = find_next_pipe(token, 0);
	if (prev && is_type(prev, PIPE))
		pipe = minipipe(mini);
	if (next && pipe != 1 && mini->no_file != 1)
		handle_pipe(mini, next->next);
	if ((prev == NULL || is_type(prev, PIPE)) && pipe != 1)
	{
		if (mini->no_file != 1)
			process_pipe_segment(mini, prev, token);
	}
}

void	execute_pipeline(t_two *cmd, t_mini *mini)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute(&cmd, mini);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		if (cmd->next)
			execute(&(cmd->next), mini);
		wait(NULL);
	}
	else
		perror("fork");
}