/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:29:03 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/24 01:19:30 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(t_mini *mini, t_two *token)
{
	t_two	*prev;
	t_two	*next;
	int		pipe;

	pipe = 0;
	prev = find_prev_pipe(token, 0);
	next = find_next_pipe(token, 0);
	if (prev && is_type(prev, PIPE))
		pipe = minipipe(mini);
	if (next && pipe != 1 && mini->no_file != 1)
		handle_pipe(mini, next->next);
	if ((prev == NULL || is_type(prev, PIPE)) && pipe != 1)
	{
		if (mini->no_file != 1)
			process_pipe_segment(mini, prev, token);
	}
}
