/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:28:07 by kikwasni          #+#    #+#             */
/*   Updated: 2025/08/01 11:04:47 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_file_after_redirect(char **tokens, int i)
{
	if (i == 0)
		return (0);
	if (has_std_redirects(tokens[i - 1]))
		return (1);
	return (0);
}

int	is_file_after_here(char **tokens, int i)
{
	if (i == 0)
		return (0);
	if (has_heredoc(tokens[i - 1]))
		return (1);
	return (0);
}

t_pars	*dolar_pars(t_pars *read)
{
	if (!extract_normal_args(read))
		return (NULL);
	expand_dollar_tokens(read);
	return (read);
}
