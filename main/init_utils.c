/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:32:26 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/24 01:32:28 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_mini *shell, char **envp)
{
	shell->envp = envp;
	shell->stdin_copy = dup(STDIN_FILENO);
	shell->stdout_copy = dup(STDOUT_FILENO);
	shell->last_exit_code = 0;
}

void	init_cmd_pars(t_pars *cmd_pars)
{
	cmd_pars->line = NULL;
	cmd_pars->tokens = NULL;
	cmd_pars->cmd = NULL;
	cmd_pars->next = NULL;
	cmd_pars->pip = 0;
}
