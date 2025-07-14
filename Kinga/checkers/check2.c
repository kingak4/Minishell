/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:11:12 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/14 14:53:20 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe_last(t_pars *read)
{
	int	i;

	i = ft_strlen(read->line) - 1;
	while (i >= 0 && ft_isspace(read->line[i]))
		i--;
	if (read->line[i] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		return (0);
	}
	return (1);
}

int	is_double_pipe(t_pars *read)
{
	int	i;

	i = 0;
	while (read->line[i])
	{
		if (read->line[i] == '|')
		{
			if (read->line[i] == '|' && (read->line[i + 1] == '|'))
			{
				write(2, "minishell: syntax error near unexpected token `||'\n", 51);
				return (0);
			}
			i++;
				while (read->line[i] && ft_isspace(read->line[i]))
					i++;
				if (read->line[i] == '|')
				{
					write(2, "minishell: syntax error near unexpected token `|'\n", 51);
					return (0);
				}
			
		}
		i++;
	}
	return (1);
}
