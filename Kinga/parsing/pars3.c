/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:52:55 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/30 15:03:24 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars	*create_new_pars_node(void)
{
	t_pars	*new_node;

	new_node = ft_calloc(1, sizeof(t_pars));
	if (!new_node)
		return (NULL);
	new_node->redirect = ft_calloc(1, sizeof(t_redirect));
	if (!new_node->redirect)
	{
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

void	split_all_pipes(t_pars *cmd)
{
	t_pars	*curr;
	t_pars	*new_node_created;

	curr = cmd;
	while (curr)
	{
		new_node_created = split_on_pipe(curr);
		if (new_node_created != NULL)
			curr = new_node_created;
		else
			curr = curr->next;
	}
}

int	find_pipe_id(t_pars *read)
{
	int	i;
	int	pipe_id;

	i = 0;
	pipe_id = -1;
	while (read->tokens[i])
	{
		if (ft_strcmp(read->tokens[i], "|") == 0)
		{
			pipe_id = i;
			break ;
		}
		i++;
	}
	return (pipe_id);
}
