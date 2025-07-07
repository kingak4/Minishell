/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:41:43 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/06 15:44:29 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int launch_program(char **args)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        // proces dziecka
        if (execvp(args[0], args) == -1)
        {
            perror("minishell");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror("fork");
    }
    else
    {
        // proces rodzica czeka
        int status;
        waitpid(pid, &status, 0);
    }
    return 1;
}

int minishell_loop(void)
{
    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    int status = 1;

    while (status)
    {
        printf("minishell$ ");
        if (!fgets(input, sizeof(input), stdin))
            break;

        // usuwamy znak nowej linii
        input[strcspn(input, "\n")] = 0;

        // dzielimy input na argumenty
        int i = 0;
        char *token = strtok(input, " ");
        while (token && i < MAX_ARGS - 1)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL)
            continue;

        if (strcmp(args[0], "cd") == 0)
            status = ft_cd(args);
        else if (strcmp(args[0], "exit") == 0)
            status = 0;
        else
            launch_program(args);
    }
    return 0;
}

int main(void)
{
    return minishell_loop();
}
