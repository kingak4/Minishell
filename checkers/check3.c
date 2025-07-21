/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:11:42 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/18 15:44:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wrap_1(int i)
{
	if (i == 1)
		write(2,
			"minishell: syntax error near unexpected token `<'\n", 51);
	else
		write(2,
			"minishell: syntax error near unexpected token `>'\n", 51);
	return (0);
}

static int	check(t_pars *read, int *i)
{
	if (read->line[*i] == '<')
		return (wrap_1(1));
	else if (read->line[*i] == '>')
		return (wrap_1(2));
	return (0);
}

int	is_double_redi1(t_pars *read, int i, char first)
{
	while (read->line[i])
	{
		while (read->line[i] && ft_isspace(read->line[i]))
			i++;
		if (read->line[i] == '>' || read->line[i] == '<')
		{
			first = read->line[i];
			i++;
			while (read->line[i] && ft_isspace(read->line[i]))
				i++;
			if (!read->line[i])
				break ;
			if ((first == '>' && read->line[i] == '<')
				|| (first == '<' && read->line[i] == '>'))
				return (check(read, &i));
		}
		if (read->line[i])
			i++;
		else
			break ;
	}
	return (1);
}

int	is_semicolon(t_pars *read)
{
	int	i;

	i = 0;
	while (read->line[i] != '\0')
	{
		if (read->line[i] == ';')
		{
			write(2, "minishell: syntax error near unexpected token `;'\n", 47);
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_operator(t_pars *read)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(read->line);
	while (i < len)
	{
		if (read->line[i] == '&' && i + 1 < len && read->line[i + 1] == '&')
		{
			write(2,
				"minishell: syntax error near unexpected token `&&'\n", 51);
			return (0);
		}
		else if (read->line[i] == '&')
		{
			write(2, "minishell: syntax error near unexpected token `&'\n", 49);
			return (0);
		}
		i++;
	}
	return (1);
}
