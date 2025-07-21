/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 08:47:46 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/21 14:41:13 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty_line(t_pars *read)
{
	int	i;

	i = 0;
	if (read == NULL || read->line == NULL)
		return (1);
	while (read->line[i])
	{
		if (!ft_isspace(read->line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	quotes_check(char *str)
{
	int	i;
	int	flag;
	int	f;

	i = 0;
	flag = 0;
	f = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' && f == 0)
			flag = !flag;
		else if (str[i] == '\'' && flag == 0)
			f = !f;
		i++;
	}
	if (flag || f)
	{
		printf("syntax error: unclosed quote\n");
		return (0);
	}
	return (1);
}

void	free_list(t_pars *read)
{
	t_pars	*current;
	t_pars	*next_node;

	if (read == NULL)
		return ;
	current = read;
	while (current != NULL)
	{
		next_node = current->next;
		free_pars(current);
		current = next_node;
	}
}

int	check_redirect_error(t_pars *read, int i)
{
	int		len;

	if (!read || !read->line)
		return (0);
	while (read->line[i])
	{
		if (read->line[i] == '>' || read->line[i] == '<')
		{
			len = 1;
			while (read->line[i + len] != '\0'
				&& read->line[i + len] == read->line[i])
				len++;
			if (len >= 3)
			{
				write(2, "minishell: syntax error near unexpected token ", 46);
				write(2, &read->line[i], len);
				write(2, "\n", 2);
				return (0);
			}
			i += len;
			continue ;
		}
		i++;
	}
	return (1);
}

int	is_pipe_first(t_pars *read)
{
	int	i;

	i = 0;
	while (read->line[i] && (read->line[i] == ' ' || read->line[i] == '\t'))
		i++;
	if (read->line[i] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `|'", 50);
		write(2, "\n", 2);
		return (0);
	}
	return (1);
}
