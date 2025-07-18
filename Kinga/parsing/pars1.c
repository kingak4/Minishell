/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:21:38 by root              #+#    #+#             */
/*   Updated: 2025/07/18 16:26:55 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(t_pars *read)
{
	int	i;

	i = 0;
	while(read->tokens[i] != NULL)
	{
		if (ft_strcmp(read->tokens[i], "|") == 0)
			return (1);
		i++;
	}
	return (0);
}
t_pars	*new_node(t_pars *read)
{
	if (!is_pipe(read))
		return (NULL);
	read->pip = 1;
	if (read->next != NULL)
        return read->next;
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
    	return;
	read->redirect->in = 0;
	read->redirect->out = 0;
	while(read->tokens[i] != NULL)
	{
		if (ft_strcmp(read->tokens[i], ">") == 0)
			read->redirect->in = 1;
		else if (ft_strcmp(read->tokens[i], ">>") == 0)
			read->redirect->in = 2;
		else if (ft_strcmp(read->tokens[i], "<") == 0)
			read->redirect->out = 1;
		else if (ft_strcmp(read->tokens[i], "<<") == 0)
			read->redirect->out = 2;
		i++;
	}
}
