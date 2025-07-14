/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:16:31 by root              #+#    #+#             */
/*   Updated: 2025/07/14 12:50:23 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// uzwaj make valgrind 
t_pars *read_cmd(t_pars *read)
{
	if (!read)
		return (NULL);
	read->line = readline("minishell>");
	if (!read->line)
		return (NULL);
	if (!is_empty_line(read))
		add_history(read->line);
	return (read);
}

t_pars	*check_read(t_pars *read)
{
	if (read == NULL ||read->line == NULL)
		return (NULL);
	if (!quotes_check(read->line))
	{
		free(read->line);
		return (NULL);
	}
	if (!check_redirect_error(read, 0))
	{
		free(read->line);
		return (NULL);
	}
	if (!is_pipe_first(read))
	{
		free(read->line);
		return (NULL);
	}
	return (read);
}

//t_cmd	*count_redirections(t_cmd *read)
//{
//	int	i;

//	i = 0;
//	read->count_redi = 0;
//	while (read->line[i] != '\0')
//	{
//		if (read->line[i] == '>' && read->line[i + 1] != '\0'
//			&& read->line[i + 1] == '>')
//			{
//				read->count_redi++;
//				i++;
//			}
//		else if (read->line[i] == '>')
//			read->count_redi++;
//		else if (read->line[i] == '<' && read->line[i + 1] != '\0'
//			&& read->line[i + 1] == '<')
//			{
//				read->count_redi++;
//				i++;
//			}
//		else if (read->line[i] == '<')
//			read->count_redi++;
//		i++;
//	}
//	return (read);
//}
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
