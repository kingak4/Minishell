/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:23:25 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/21 20:46:40 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_cmd_error(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

void	exec_external(char **args, char **envp)
{
	pid_t	pid;
	int		status;
	char	*full_path;

	pid = fork();
	if (pid == 0)
	{
		full_path = find_cmd_path(args[0], envp);
		if (full_path)
		{
			execve(full_path, args, envp);
			perror("execve");
			free(full_path);
		}
		else
			print_cmd_error(args[0]);
		exit(127);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("fork");
}
