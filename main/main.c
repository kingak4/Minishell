/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:41:43 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/21 20:53:29 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_two	*convert_to_t_two(t_pars *pars)
{
	t_two	*cmd;

	cmd = malloc(sizeof(t_two));
	if (!cmd)
		return (NULL);
	cmd->args = pars->tokens;
	cmd->cmd = cmd->args[0];
	cmd->redirect = NULL;
	cmd->next = NULL;
	cmd->str = NULL;
	return (cmd);
}

void execute(t_two **cmd, t_mini *shell)
{
    if (!cmd || !*cmd)
        return;

    if (is_builtin((*cmd)->cmd))
    {
        exec_builtin((*cmd)->args, shell);
    }
    else
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            exec_external((*cmd)->args, shell->envp);
            perror("exec_external");
            exit(EXIT_FAILURE);
        }
        else if (pid > 0)
        {
            waitpid(pid, NULL, 0);
        }
        else
        {
            perror("fork");
        }
    }
}
int	main(int argc, char **argv, char **envp)
{
	t_pars	cmd_pars;
	t_two	*cmd_two;
	t_mini	shell;

	(void)argc;
	(void)argv;
	shell.envp = envp;
	shell.stdin_copy = dup(STDIN_FILENO);
	shell.stdout_copy = dup(STDOUT_FILENO);
	shell.last_exit_code = 0;
	while (1)
	{
		cmd_pars.line = NULL;
		cmd_pars.tokens = NULL;
		cmd_pars.cmd = NULL;
		cmd_pars.next = NULL;
		cmd_pars.pip = 0;
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
		execute(&cmd_two, &shell);
		free(cmd_pars.line);
		free(cmd_two);
		rl_clear_history();
	}
	return (0);
}