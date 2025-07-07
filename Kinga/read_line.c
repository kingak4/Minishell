/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:16:31 by root              #+#    #+#             */
/*   Updated: 2025/07/03 10:47:33 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_cmd
{
	char	*line;
	char	**redi_file;
	int		*redi_signal;
	int		count_redi;
}	t_cmd;

t_cmd *read_cmd(t_cmd *read)
{
	if (!read)
		return (NULL);
	read->line = readline("minishell");
	if (!read->line)
		return (NULL);
	return (read);
}
int check_redirect_error(t_cmd *read, int pos)
{
	int count;
	int i;
	char c;

	if (!read || !read->line)
		return (0);
	count = 0;
	i = pos;
	c = read->line[pos];
	while (read->line[i] && read->line[i] == c)
	{
		count++;
		i++;
	}
	if (count >= 3)
	{
		write(2, "minishell: syntax error near unexpected token '", 46);
		write(2, &read->line[pos], count);
		write(2, "'\n", 2);
		return (0);
	}
	return (1);
}
t_cmd	*count_redirections(t_cmd *read)
{
	int	i;

	i = 0;
	read->count_redi = 0;
	while (read->line[i] != '\0')
	{
		if (read->line[i] == '>' && read->line[i + 1] != '\0'
			&& read->line[i + 1] == '>')
			{
				read->count_redi++;
				i++;
			}
		else if (read->line[i] == '>')
			read->count_redi++;
		else if (read->line[i] == '<' && read->line[i + 1] != '\0'
			&& read->line[i + 1] == '<')
			{
				read->count_redi++;
				i++;
			}
		else if (read->line[i] == '<')
			read->count_redi++;
		i++;
	}
	return (read);
}
// do naprawy szkieliet to jest
//t_cmd *parse_redirect(t_cmd *read, int pos)
//{
//	int size;
//	int i;

//	size = 0;
//	i = 0;
//	if (check_redirect_error(read, pos) == 0)
//		return (NULL);
//	while (read->line[size])
//		size++;
//	while (i < size)
//	{
//		if (read->line[i] == '>')
//			read->redi_signal = 1;
//		else if (read->line[i + 1] == '>')
//			read->redi_signal = 2;
//		else if (read->line[i] == '<')
//			read->redi_signal = 3;
//		else if (read->line[i + 1] == '<')
//			read->redi_signal = 3;
//		i++;
//	}
//	return (read);
//}
// t_cmd	*check_red(t_cmd *read)
// {
//     int i;

//     i = 0;
//     read->line = read_cmd(read);
//     if (!read->line)
//         return (NULL);
//     while (read->line)
//     {

//     }

// }
//int main(void)
//{
//	t_cmd cmd;

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
int main(void)
{
    t_cmd cmd;
    char *input;

    while (1)
    {
        input = readline("minishell> ");
        if (!input)
        {
            printf("\nKoniec wejścia. Kończę program.\n");
            break;
        }

        cmd.line = input;
        cmd.count_redi = 0;

        count_redirections(&cmd);

        printf("Linia: \"%s\"\n", cmd.line);
        printf("Znaleziono redirekcji: %d\n\n", cmd.count_redi);

        free(input);
    }

    return 0;
}
