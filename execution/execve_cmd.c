/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:23:25 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/16 17:54:09 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_external(char **args, char **envp)
{
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		execve(args[0], args, envp);
		perror("execve");
		exit(127);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("fork");
}
