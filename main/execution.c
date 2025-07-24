/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:31:39 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/24 01:31:44 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_fork(t_two *cmd, t_mini *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		exec_external(cmd->args, shell->envp);
		perror("exec_external");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("fork");
}

void	execute(t_two **cmd, t_mini *shell)
{
	if (!cmd || !*cmd)
		return ;
	if (is_builtin((*cmd)->cmd))
		exec_builtin((*cmd)->args, shell);
	else
		exec_fork(*cmd, shell);
}
