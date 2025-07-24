/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:41:43 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/24 01:35:48 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_shell_loop(t_mini *shell)
{
	t_pars	cmd_pars;
	t_two	*cmd_two;

	while (1)
	{
		init_cmd_pars(&cmd_pars);
		if (!read_cmd(&cmd_pars))
			break ;
		if (!check_read(&cmd_pars))
		{
			free(cmd_pars.line);
			continue ;
		}
		lex(&cmd_pars);
		cmd_two = convert_to_t_two(&cmd_pars);
		if (!cmd_two)
			continue ;
		execute(&cmd_two, shell);
		free(cmd_pars.line);
		free(cmd_two);
		rl_clear_history();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	run_shell_loop(&shell);
	return (0);
}
