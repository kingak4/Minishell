/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulitin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:46:15 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/20 22:40:08 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	exec_builtin(char **args, t_mini *shell)
{
	if (!args || !args[0])
		return (1);
	if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(args));
	if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(args));
	if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(args[0], "env"))
		return (ft_env(shell->envp));
	if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(args, shell));
	if (!ft_strcmp(args[0], "exit"))
		ft_exit(args, shell);
	return (1);
}