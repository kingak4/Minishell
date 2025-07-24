/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:19:44 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/24 01:19:51 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

int	is_type(t_two *token, int type)
{
	if (!token)
		return (0);
	if (type == PIPE)
		return (token->str && ft_strcmp(token->str, "|") == 0);
	if (!token->redirect)
		return (0);
	if (type == TRUNC)
		return (token->redirect->out == 1);
	if (type == APPEND)
		return (token->redirect->out == 2);
	if (type == INPUT)
		return (token->redirect->in == 1);
	if (type == INPUT_ECHO)
		return (token->redirect->in == 2);
	return (0);
}
