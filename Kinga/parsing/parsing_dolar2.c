/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dolar2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:46:12 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/24 14:19:34 by kikwasni         ###   ########.fr       */
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
	read->var = 0;
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

t_pars	*dolar_pars(t_pars *read)
{
	int	i;
	int	a;

	if (!dolar_checker(read))
		return (NULL);
	read->args = malloc(sizeof(char *) * 101);
	if (!read->args)
		return (NULL);
	i = 0;
	a = 0;
	while (read->tokens[i])
	{
		process_token(read, i, &a);
		i++;
	}
	read->args[a] = NULL;
	return (read);
}
