/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:48:53 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/23 14:37:47 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	quote_is_g(char c, char quote)
{
	if (c == '\"')
	{
		if (quote == 0)
			return (c);
		else if (quote == c)
			return (0);
	}
	return (quote);
}
int	flag_checker(t_pars *read)
{
	int		i;
	char	q;
	int		j;
	int		d;
	int		space;
	int		d_out;

	i = 0;
	while (read->tokens[i] != NULL)
	{
		q = 0;
		j = 0;
		space = 0;
		d = 0;
		d_out = 0;
		while(read->tokens[i][j] != '\0')
		{
			q = quote_is_g(read->tokens[i][j], q);
			if (q != 0)
			{
				if (read->tokens[i][j] == '-')
					d = 1;
				else if (read->tokens[i][j] == ' ')
					space = 1;
			}
			else
			{
				if (read->tokens[i][j + 1] && read->tokens[i][j] == '-' && ft_isprint(read->tokens[i][j + 1]))
					d_out = 1;
			}
			j++;
		}
		if (d_out)
			return (1);
		if (d && !space)
			return (1);
		i++;
	}
	return (0);
}
t_pars	*flag_pars(t_pars *read)
{
	int	i;
	int	j;
	int	f;
	char	q;
	int	start;
	
	if (!flag_checker(read))
		return(NULL);
	read->flags = malloc(sizeof(char *) * (100 + 1));
	if (!read->flags)
		return (NULL);
	i = 0;
	f = 0;
	while (read->tokens[i] != NULL)
	{
		j = 0;
		q = 0;
		start = -1;
		while(read->tokens[i][j] != '\0')
		{
			q = quote_is_g(read->tokens[i][j], q);
			if (q)
			{
				read->flags[f++] = remove_hyphens(&read->tokens[i][j]);
				read->tokens[i][j] = '\0';
				break;
			}
			else
			{
				if (read->tokens[i][j + 1] && read->tokens[i][j] == '-' && ft_isprint(read->tokens[i][j + 1]))
				{
					start = j;
					break ;	
				}
				j++;
			}
		}
		if ( start != -1)
		{
			read->flags[f] = ft_strdup(&read->tokens[i][start]);
			f++; 
			read->tokens[i][start] = '\0';
		}
		i++;
	}
	read->flags[f] = NULL;
	return (read);
}
