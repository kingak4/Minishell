/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dolar2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:46:12 by kikwasni          #+#    #+#             */
/*   Updated: 2025/08/01 11:02:18 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	save_dolar_from_quote(t_pars *read, int i, int j, int *a)
{
	char	*var_name;

	read->var = 1;
	var_name = &read->tokens[i][j + 2];
	read->args[*a] = remove_hyphens(var_name);
	read->tokens[i][j] = '\0';
	(*a)++;
}

static void	save_dolar_direct(t_pars *read, int i, int start, int *a)
{
	read->args[*a] = ft_strdup(&read->tokens[i][start]);
	read->tokens[i][start] = '\0';
	(*a)++;
}

static void	process_token(t_pars *read, int i, int *a)
{
	int		j;
	char	q;
	int		start;

	j = 0;
	q = 0;
	start = -1;
	while (read->tokens[i][j])
	{
		q = quote_is_g(read->tokens[i][j], q);
		if (q)
			return (save_dolar_from_quote(read, i, j, a));
		else if (read->tokens[i][j + 1] && read->tokens[i][j] == '$'
			&& ft_isprint(read->tokens[i][j + 1]))
		{
			read->var = 1;
			start = ++j;
			break ;
		}
		j++;
	}
	if (start != -1)
		save_dolar_direct(read, i, start, a);
}

int	extract_normal_args(t_pars *read)
{
	int	i;
	int	a;

	read->args = malloc(sizeof(char *) * 101);
	if (!read->args)
		return (0);
	i = 0;
	a = 0;
	read->var = 0;
	while (read->tokens[i])
	{
		if (is_normal_arg(read, i)
			&& !is_file_after_redirect(read->tokens, i)
			&& !is_file_after_here(read->tokens, i))
		{
			read->args[a] = remove_hyphens(read->tokens[i]);
			read->tokens[i][0] = '\0';
			a++;
		}
		i++;
	}
	read->args[a] = NULL;
	return (1);
}

void	expand_dollar_tokens(t_pars *read)
{
	int	i;
	int	a;

	a = 0;
	while (read->args && read->args[a])
		a++;
	while (dolar_checker(read))
	{
		i = 1;
		while (read->tokens[i])
		{
			process_token(read, i, &a);
			i++;
		}
	}
	read->args[a] = NULL;
}
