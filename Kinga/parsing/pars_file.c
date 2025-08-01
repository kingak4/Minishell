/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:27:09 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/31 12:37:39 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_files(t_pars *read)
{
	int	i;
	int	g;

	i = 0;
	g = 0;
	read->file = malloc(sizeof(char *) * 101);
	if (!read->file)
		return ;
	while (read->tokens[i] != NULL)
	{
		if (has_std_redirects(read->tokens[i]))
		{
			if (read->tokens[i + 1] != NULL)
			{
				read->file[g++] = ft_strdup(read->tokens[i + 1]);
				i += 2;
				continue ;
			}
		}
		i++;
	}
	read->file[g] = NULL;
}

void	pars_here_doc(t_pars *read)
{
	int	i;
	int	g;

	i = 0;
	g = 0;
	read->deli = malloc(sizeof(char *) * 101);
	if (!read->deli)
		return ;
	while (read->tokens[i] != NULL)
	{
		if (has_heredoc(read->tokens[i]))
		{
			if (read->tokens[i + 1] != NULL)
			{
				read->deli[g++] = ft_strdup(read->tokens[i + 1]);
				i += 2;
				continue ;
			}
		}
		i++;
	}
	read->deli[g] = NULL;
}
//void	pars_cmd(t_pars *read)
//{
//	int	i;
//	int	f;

//	i = 0;
//	f = 0;
//	read->flags = malloc(sizeof(char *) * 101);
//	if (!read->flags)
//		return ;
//	if (is_redi_first(read))
//		return ;
//	while (read->tokens[i] != NULL)
//	{
//		if (read->tokens != NULL && read->tokens[i] != NULL
//			&& ft_isalpha(read->tokens[i][0] && !flag_checker(read)))
//		{
//			read->flags[f] = ft_strdup(read->tokens[i]);
//			read->tokens[i] = NULL;
//			f++;
//		}
//		i++;
//	}
//	if (read->flags)
//		read->flags[f] = NULL;
//}
