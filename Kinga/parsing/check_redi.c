/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:53:31 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/30 15:02:22 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_std_redirects(const char *token)
{
	return (token && (ft_strcmp(token, "<") == 0
			|| ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0));
}

int	has_heredoc(const char *token)
{
	return (token && ft_strcmp(token, "<<") == 0);
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
