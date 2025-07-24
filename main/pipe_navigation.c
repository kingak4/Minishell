/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_navigation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:20:17 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/24 01:20:21 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_two	*find_prev_pipe(t_two *token, int skip)
{
	t_two	*curr;

	curr = token;
	while (curr)
	{
		if (is_type(curr, PIPE))
		{
			if (skip == 0)
				return (curr);
			skip--;
		}
		curr = curr->next;
	}
	return (NULL);
}

t_two	*find_next_pipe(t_two *token, int skip)
{
	t_two	*curr;

	curr = token;
	while (curr)
	{
		if (is_type(curr, PIPE))
		{
			if (skip == 0)
				return (curr);
			skip--;
		}
		curr = curr->next;
	}
	return (NULL);
}
