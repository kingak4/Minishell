/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:21:38 by root              #+#    #+#             */
/*   Updated: 2025/07/28 15:57:07 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(t_pars *read)
{
	int	i;

	i = 0;
	while (read->tokens[i] != NULL)
	{
		if (ft_strcmp(read->tokens[i], "|") == 0)
			return (1);
		i++;
	}
	return (0);
}

t_pars	*init_pars(t_pars *read)
{
	read = ft_calloc(1, sizeof(t_pars));
	if (!read)
		return (NULL);
	read->redirect = ft_calloc(1, sizeof(t_redirect));
	if (!read->redirect)
	{
		free(read);
		return (NULL);
	}
	return (read);
}

t_pars	*new_node(t_pars *read)
{
	if (!is_pipe(read))
		return (NULL);
	read->pip = 1;
	if (read->next != NULL)
		return (read->next);
	read->next = ft_calloc(1, sizeof(t_pars));
	if (!read->next)
		return (NULL);
	return (read->next);
}

void	is_redi(t_pars *read)
{
	int	i;

	i = 0;
	if (!read->redirect)
		return ;
	read->redirect->r_in = 0;
	read->redirect->r_out = 0;
	read->redirect->r_app = 0;
	read->redirect->r_hdoc = 0;
	while (read->tokens[i] != NULL)
	{
		if (ft_strcmp(read->tokens[i], ">") == 0)
			read->redirect->r_in++;
		else if (ft_strcmp(read->tokens[i], ">>") == 0)
			read->redirect->r_app++;
		else if (ft_strcmp(read->tokens[i], "<") == 0)
			read->redirect->r_out++;
		else if (ft_strcmp(read->tokens[i], "<<") == 0)
			read->redirect->r_hdoc++;
		i++;
	}	
}

void	free_pars(t_pars *read)
{
	if (!read)
		return ;
	if (read->redirect)
		free(read->redirect);
	if (read->tokens)
		free_tab(read->tokens);
	if (read->line)
		free(read->line);
	if (read->flags)
		free_tab(read->flags);
	if (read->args)
		free_tab(read->args);
	free(read);
}
