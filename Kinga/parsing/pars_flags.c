/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:48:53 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/24 16:40:47 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	quote_is_g(char c, char quote)
{
	if (c == '\"')
	{
		if (quote == 0)
			return (c);
		else if (quote == c)
			return (0);
	}
	else if (c == '\'')
		return (-1);
	return (quote);
}

static void	init_flags(char *q, int *space, int *d, int *d_out)
{
	*q = 0;
	*space = 0;
	*d = 0;
	*d_out = 0;
}

static void	check_token(const char *token, int *d, int *space, int *d_out)
{
	int		j;
	char	q;

	j = 0;
	init_flags(&q, space, d, d_out);
	while (token[j])
	{
		q = quote_is_g(token[j], q);
		if (q != 0 && q != -1)
		{
			if (token[j] == '-')
				(*d) = 1;
			else if (token[j] == ' ')
				(*space) = 1;
		}
		else if (token[j + 1] && token[j] == '-' && ft_isprint(token[j + 1])
			&& q != -1)
			(*d_out) = 1;
		else if (q == -1)
			(*d_out) = 0;
		j++;
	}
}

int	flag_checker(t_pars *read)
{
	int	i;
	int	d;
	int	space;
	int	d_out;

	i = 0;
	while (read->tokens[i])
	{
		check_token(read->tokens[i], &d, &space, &d_out);
		if (d_out || (d && !space))
			return (1);
		i++;
	}
	return (0);
}
