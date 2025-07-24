/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:31:58 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/24 01:32:01 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_two	*convert_to_t_two(t_pars *pars)
{
	t_two	*cmd;

	cmd = malloc(sizeof(t_two));
	if (!cmd)
		return (NULL);
	cmd->args = pars->tokens;
	cmd->cmd = cmd->args[0];
	cmd->redirect = NULL;
	cmd->next = NULL;
	cmd->str = NULL;
	return (cmd);
}
