/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:11:12 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/16 10:14:30 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe_last(t_pars *read)
{
	int	i;

	i = ft_strlen(read->line) - 1;
	while (i >= 0 && ft_isspace(read->line[i]))
		i--;
	if (i >= 0 && read->line[i] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		return (0);
	}
	return (1);
}

int	is_double_pipe(t_pars *read, int i)
{
	while (read->line[i])
	{
		if (read->line[i] == '|')
		{
			if (read->line[i] == '|' && (read->line[i + 1] == '|'))
			{
				write(2,
					"minishell: syntax error near unexpected token `|'\n", 51);
				return (0);
			}
			i++;
			while (read->line[i] && ft_isspace(read->line[i]))
				i++;
			if (read->line[i] == '|')
			{
				write(2,
					"minishell: syntax error near unexpected token `|'\n", 51);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

static int	wrap(void)
{
	write(2,
		"minishell: syntax error near unexpected token `|'\n", 51);
	return (0);
}

int	is_redi_and_pipe(t_pars *read, int i, int len)
{
	len = ft_strlen(read->line);
	while (read->line[i])
	{
		if (read->line[i] == '>' || read->line[i] == '<')
		{
			if (i + 1 < len && read->line[i + 1] == read->line[i])
				i++;
			if (read->line[i] == '>' && (i == 0 || read->line[i - 1] != '>')
				&& i + 1 < len && read->line[i + 1] == '|')
			{
				i += 2;
				continue ;
			}
			i++;
			while (i < len && ft_isspace(read->line[i]))
				i++;
			if (i < len && read->line[i] == '|')
				return (wrap());
			if (i >= len || read->line[i] == '\0')
				return (wrap());
		}
		i++;
	}
	return (1);
}

int	is_redi1_last(t_pars *read)
{
	int	i;

	i = ft_strlen(read->line) - 1;
	while (i >= 0 && ft_isspace(read->line[i]))
		i--;
	if (i >= 0 && (read->line[i] == '>' || read->line[i] == '<'))
	{
		write(2,
			"minishell: syntax error near unexpected token `newline'\n", 58);
		return (0);
	}
	return (1);
}
