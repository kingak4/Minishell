/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:41:43 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/23 14:43:17 by kikwasni         ###   ########.fr       */
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

// int main(void)
//{
//     return minishell_loop();
// }

// int main(void)
//{
//	t_pars cmd;

//	while (1)
//	{
//		if (!read_cmd(&cmd))
//		{
//			printf("\nKoniec lub blad odczytu. Koncze program.\n");
//			break;
//		}

//		printf("Wczytano linie: %s\n", cmd.line);

//		free(cmd.line);
//	}
//	rl_clear_history();
//	return 0;
//}
// int main(void)
// {
// 	t_pars cmd;

// 	while (1)
// 	{
// 		if (!read_cmd(&cmd))
// 		{
// 			printf("\nKoniec lub blad odczytu. Koncze program.\n");
// 			break;
// 		}

// 		if (!check_read(&cmd))
// 		{
// 			continue;
// 		}

// 		printf("Wczytano linie: %s\n", cmd.line);
// 	}

// 	rl_clear_history();
// 	return 0;
// }
// int main(void)
//{
//     char **tokens;
//     int i;

//    char *test = "echo  $  \"$USER\" \'$this is\' a test";

//    tokens = ft_split_mini(test, ' ');
//    if (!tokens)
//    {
//        printf("Błąd alokacji pamięci!\n");
//        return 1;
//    }

//    i = 0;
//    while (tokens[i])
//    {
//        printf("Token %d: [%s]\n", i, tokens[i]);
//        i++;
//    }

//    i = 0;
//    while (tokens[i])
//        free(tokens[i++]);
//    free(tokens);

//    return 0;
//}
// int main()
//{
//	char *s = " 														\'        kd\'";
//	char *rest = space(s);
//	printf("%s\n", rest);
//}

// int main()
//{
//	char *s = "echo \"$USER\" $ \'$this is\' a test";
//	char *rest = remove_hyphens(s);
//	printf("%s\n", rest);
//}
// int	main(void)
// {
// 	t_pars	cmd;
// 	int		i;

// 	// 1. Wczytaj input raz
// 	cmd.line = readline("minishell> ");

// 	// 2. Jeśli coś poszło nie tak – koniec
// 	if (!cmd.line)
// 	{
// 		printf("Brak inputu. Kończę program.\n");
// 		return (1);
// 	}

// 	// 3. Tokenizacja przez lex()
// 	if (!lex(&cmd))
// 	{
// 		printf("Błąd podczas tokenizacji.\n");
// 		return (1);
// 	}

// 	// 4. Wydrukuj wszystkie tokeny
// 	printf("Tokeny:\n");
// 	i = 0;
// 	while (cmd.tokens && cmd.tokens[i])
// 	{
// 		printf("  [%d]: %s\n", i, cmd.tokens[i]);
// 		i++;
// 	}

// 	// 5. Sprawdź, czy zawiera pipe
// 	if (is_pipe(&cmd))
// 		printf("✅ Wykryto pipe!\n");
// 	else
// 		printf("❌ Brak pipe w tokenach.\n");

// 	// 6. Zwolnij pamięć, wyczyść historię
// 	free(cmd.line);
// 	i = 0;
// 	while (cmd.tokens && cmd.tokens[i])
// 		free(cmd.tokens[i++]);
// 	free(cmd.tokens);
// 	rl_clear_history();

// 	return (0);
// }
// int main(void)
// {
//     t_pars cmd;
//     int i;

//     // Inicjuj wskaźniki na NULL
//     cmd.tokens = NULL;
//     cmd.next = NULL;
//     cmd.pip = 0;
//     cmd.line = NULL;

//     cmd.line = readline("minishell> ");
//     if (!cmd.line)
//     {
//         printf("Brak inputu. Kończę program.\n");
//         return (1);
//     }

//     if (!lex(&cmd))
//     {
//         printf("Błąd podczas tokenizacji.\n");
//         free(cmd.line);
//         return (1);
//     }

//     printf("Tokeny:\n");
//     i = 0;
//     while (cmd.tokens && cmd.tokens[i])
//     {
//         printf("  [%d]: %s\n", i, cmd.tokens[i]);
//         i++;
//     }

//     if (is_pipe(&cmd))
//     {
//         printf("✅ Wykryto pipe!\n");
//         t_pars *new = new_node(&cmd);
//         if (new)
//             printf("Nowy node został utworzony.\n");
//         else
//             printf("Nie udało się utworzyć nowego node.\n");
//     }
//     else
//     {
//         printf("❌ Brak pipe w tokenach.\n");
//     }

//     // Czyszczenie pamięci
//     free(cmd.line);
//     i = 0;
//     while (cmd.tokens && cmd.tokens[i])
//         free(cmd.tokens[i++]);
//     free(cmd.tokens);

//     if (cmd.next)
//         free(cmd.next);

//     rl_clear_history();

//     return 0;
// }
//int	main(void)
//{
//	t_pars	*read;
//	int		i;

//	read = init_pars(NULL);
//	if (!read)
//		return (1);

//	if (read_cmd(read) && lex(read))
//	{
//		printf("Tokens:\n");
//		i = 0;
//		while (read->tokens && read->tokens[i])
//		{
//			printf("[%s]\n", read->tokens[i]);
//			i++;
//		}
//		free_tab(read->tokens);
//		read->tokens = NULL;
//	}
//	//free(read->line);
//	read->line = NULL;

//	// czyszczenie końcowe
//	free_pars(read);
//	rl_clear_history();
//	rl_free_line_state();

//	return (0);
//int	main(void)
//{
//	t_pars	*cmd;

//	while (1)
//	{
//		cmd = init_pars(NULL);
//		if (!cmd)
//			break;

//		if (!read_cmd(cmd))
//		{
//			printf("\nKoniec lub błąd odczytu. Kończę program.\n");
//			free_list(cmd);
//			break;
//		}

//		if (!lex(cmd))
//		{
//			free_list(cmd);
//			continue;
//		}

//		is_redi(cmd);
//		cmd->pip = is_pipe(cmd);

//		printf("Wczytano: %s\n", cmd->line);
//		if (cmd->tokens)
//		{
//			for (int i = 0; cmd->tokens[i]; i++)
//				printf("  [%d]: %s\n", i, cmd->tokens[i]);
//		}

//		if (cmd->redirect)
//		{
//			printf("Redirekcje:\n");
//			printf("  >  : %d\n", cmd->redirect->r_in);
//			printf("  >> : %d\n", cmd->redirect->r_app);
//			printf("  <  : %d\n", cmd->redirect->r_out);
//			printf("  << : %d\n", cmd->redirect->r_hdoc);
//		}

//		if (cmd->pip)
//			printf("Zawiera pipe'y.\n");
//		if (flag_checker(cmd))
//			printf("zwrócil 1\n");
//		else
//			printf("zwrócił 0\n");
//		if (flag_checker(cmd))
//			printf("Zwrócił 1 – znaleziono flagi\n");
			
//	if (flag_pars(cmd))
//	{
//		printf("Flagi:\n");
//		for (int i = 0; cmd->flags && cmd->flags[i]; i++)
//		printf("  [flag %d]: %s\n", i, cmd->flags[i]);
		
//		printf("Tokeny po usunięciu flag:\n");
//		for (int i = 0; cmd->tokens && cmd->tokens[i]; i++)
//		printf("  [tok %d]: %s\n", i, cmd->tokens[i]);
//	}
//	else
//		printf("Błąd podczas parsowania flag.\n");
//	}
//	free_list(cmd);
//	rl_clear_history();
//	return (0);
//}
int main(void)
{
    t_pars *cmd = NULL;

    while (1)
    {
        if (cmd)
        {
            free_list(cmd);
            cmd = NULL;
        }

        cmd = init_pars(NULL);
        if (!cmd)
            break;

        if (!read_cmd(cmd))
        {
            printf("\nKoniec lub błąd odczytu. Kończę program.\n");
            break;
        }

        if (!lex(cmd))
            continue;

        is_redi(cmd);
        cmd->pip = is_pipe(cmd);

        printf("Wczytano: %s\n", cmd->line);
        if (cmd->tokens)
        {
            for (int i = 0; cmd->tokens[i]; i++)
                printf("  [%d]: %s\n", i, cmd->tokens[i]);
        }

        if (cmd->redirect)
        {
            printf("Redirekcje:\n");
            printf("  >  : %d\n", cmd->redirect->r_out);
            printf("  >> : %d\n", cmd->redirect->r_app);
            printf("  <  : %d\n", cmd->redirect->r_in);
            printf("  << : %d\n", cmd->redirect->r_hdoc);
        }

        if (cmd->pip)
            printf("Zawiera pipe'y.\n");

        int flags_found = flag_checker(cmd);
        if (flags_found)
        {
            printf("Znaleziono flagi\n");
        }
        else
            printf("Nie znaleziono flag\n");

        if (flags_found && flag_pars(cmd))
        {
            printf("Flagi:\n");
            for (int i = 0; cmd->flags && cmd->flags[i]; i++)
                printf("  [flag %d]: %s\n", i, cmd->flags[i]);

            printf("Tokeny po usunięciu flag:\n");
            for (int i = 0; cmd->tokens && cmd->tokens[i]; i++)
                printf("  [tok %d]: %s\n", i, cmd->tokens[i]);
        }
        else if (flags_found)
            printf("Błąd podczas parsowania flag.\n");
    }
    if (cmd)
        free_list(cmd);

    rl_clear_history();
    return 0;
}