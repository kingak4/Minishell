/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:41:43 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/18 16:30:20 by root             ###   ########.fr       */
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
//	char *s = "hello\t\tworld";
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
int	main(void)
{
	t_pars	cmd;
	int		i;

	// Inicjalizacja pól struktury
	cmd.tokens = NULL;
	cmd.next = NULL;
	cmd.pip = 0;
	cmd.line = NULL;
	cmd.redirect = calloc(1, sizeof(t_redirect)); // WAŻNE: inicjalizacja struktury redirect

	// Pobranie inputu
	cmd.line = readline("minishell> ");
	if (!cmd.line)
	{
		printf("Brak inputu. Kończę program.\n");
		return (1);
	}

	// Tokenizacja (tu możesz podmienić na własną funkcję)
	if (!lex(&cmd))
	{
		printf("Błąd podczas tokenizacji.\n");
		free(cmd.line);
		return (1);
	}

	// Wypisz tokeny
	printf("Tokeny:\n");
	i = 0;
	while (cmd.tokens && cmd.tokens[i])
	{
		printf("  [%d]: %s\n", i, cmd.tokens[i]);
		i++;
	}

	// Sprawdzenie redirekcji
	is_redi(&cmd);

	printf("\n🎯 Wykryto redirekcje:\n");
	printf("IN:  %d \n", cmd.redirect->in);
	printf("OUT: %d \n", cmd.redirect->out);

	// Czyszczenie
	free(cmd.line);
	i = 0;
	while (cmd.tokens && cmd.tokens[i])
		free(cmd.tokens[i++]);
	free(cmd.tokens);
	free(cmd.redirect);
	if (cmd.next)
		free(cmd.next);
	rl_clear_history();

	return (0);
}