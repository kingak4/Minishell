/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:19:38 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/31 11:50:08 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_red(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_strcmp(&s[i], ">") == 0)
			return (1);
		else if (ft_strcmp(&s[i], ">>") == 0)
			return (1);
		else if (ft_strcmp(&s[i], "<") == 0)
			return (1);
		else if (ft_strcmp(&s[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_normal_arg(t_pars *read, int i)
{
	if (i == 0)
		return (0);
	if (flag_checker1(read->tokens[i]))
		return (0);
	if (is_red(read->tokens[i]))
		return (0);
	if (ft_strcmp(read->tokens[i], "|") == 0)
		return (0);
	if (read->tokens[i][0] == '$')
		return (0);
	return (1);
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

int	flag_checker1(char *token)
{
	int	d;
	int	space;
	int	d_out;

	check_token(token, &d, &space, &d_out);
	if (d_out || (d && !space))
		return (1);
	return (0);
}