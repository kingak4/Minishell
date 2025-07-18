/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:04:46 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/16 13:44:51 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars	*lex(t_pars *read)
{
	if (!check_read(read))
		return (NULL);
	read->tokens = ft_split_mini(read->line, ' ');
	return (read);
}
