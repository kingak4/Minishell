/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_flags2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 08:39:21 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/29 10:08:36 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	save_flag_from_quote(t_pars *read, int i, int j, int *f)
{
	read->flags[*f] = remove_hyphens(&read->tokens[i][j]);
	read->tokens[i][j] = '\0';
	(*f)++;
}

static void	save_flag_direct(t_pars *read, int i, int start, int *f)
{
	read->flags[*f] = ft_strdup(&read->tokens[i][start]);
	read->tokens[i][start] = '\0';
	(*f)++;
}

static void	process_token(t_pars *read, int i, int *f)
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
		if (q && read->tokens[i][j + 1] && read->tokens[i][j] == '-')
			return (save_flag_from_quote(read, i, j, f));
		else if (read->tokens[i][j + 1] && read->tokens[i][j] == '-'
			&& ft_isprint(read->tokens[i][j + 1]))
		{
			start = j;
			break ;
		}
		j++;
	}
	if (start != -1)
		save_flag_direct(read, i, start, f);
}

t_pars	*flag_pars(t_pars *read)
{
	int	i;
	int	f;

	if (!flag_checker(read))
		return (NULL);
	read->flags = malloc(sizeof(char *) * 101);
	if (!read->flags)
		return (NULL);
	i = 0;
	f = 0;
	while (read->tokens[i])
	{
		process_token(read, i, &f);
		i++;
	}
	read->flags[f] = NULL;
	return (read);
}
