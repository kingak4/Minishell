/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:53:31 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/28 16:15:32 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_std_redirects(t_pars *read)
{
	if (!read || !read->redirect)
		return (0);
	return (read->redirect->r_in > 0
		|| read->redirect->r_out > 0
		|| read->redirect->r_app > 0);
}

int	has_heredoc(t_pars *read)
{
	if (!read || !read->redirect)
		return (0);
	return (read->redirect->r_hdoc > 0);
}

int	is_redi_first(t_pars *read)
{
	if (read->tokens[0] != NULL && read->tokens[1] != NULL)
	{
		if (ft_strcmp(read->tokens[0], ">") == 0)
			return (1);
		else if (ft_strcmp(read->tokens[0], ">>") == 0)
			return (1);
		else if (ft_strcmp(read->tokens[0], "<") == 0)
			return (1);
		else if (ft_strcmp(read->tokens[0], "<<") == 0)
			return (1);
	}
	return (0);
}
