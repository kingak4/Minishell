/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:19:51 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/30 15:05:54 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_t(char **tokens, int pipe_id)
{
	int	count;

	count = 0;
	while (tokens[++pipe_id])
		count++;
	return (count);
}

static int	copy_tokens_after_pipe(t_pars *new_node, char **tokens, int pipe_id)
{
	int	i;
	int	start;

	i = 0;
	start = pipe_id + 1;
	new_node->tokens = ft_calloc(count_t(tokens, pipe_id) + 1, sizeof(char *));
	if (!new_node->tokens)
		return (0);
	while (tokens[start])
	{
		new_node->tokens[i] = ft_strdup(tokens[start]);
		if (!new_node->tokens[i])
		{
			free_tab(new_node->tokens);
			return (0);
		}
		i++;
		start++;
	}
	new_node->tokens[i] = NULL;
	return (1);
}

static int	copy_t(t_pars *read, char **old_tokens, int pipe_id)
{
	int	i;

	i = 0;
	read->tokens = ft_calloc(pipe_id + 1, sizeof(char *));
	if (!read->tokens)
		return (0);
	while (i < pipe_id)
	{
		read->tokens[i] = ft_strdup(old_tokens[i]);
		if (!read->tokens[i])
		{
			free_tab(read->tokens);
			return (0);
		}
		i++;
	}
	read->tokens[i] = NULL;
	return (1);
}

static void	insert_node_after_current(t_pars *read, t_pars *new_node)
{
	t_pars	*tmp;

	tmp = read->next;
	read->next = new_node;
	new_node->next = tmp;
}

t_pars	*split_on_pipe(t_pars *read)
{
	int		pipe_id;
	t_pars	*new_node;
	char	**old_tokens;

	if (!read || !read->tokens)
		return (NULL);
	pipe_id = find_pipe_id(read);
	if (pipe_id == -1 || !read->tokens[pipe_id + 1])
		return (NULL);
	read->pip = 1;
	new_node = create_new_pars_node();
	if (!new_node)
		return (NULL);
	old_tokens = read->tokens;
	if (!copy_tokens_after_pipe(new_node, old_tokens, pipe_id)
		|| !copy_t(read, old_tokens, pipe_id))
	{
		free_tab(old_tokens);
		free_pars(new_node);
		return (NULL);
	}
	free_tab(old_tokens);
	insert_node_after_current(read, new_node);
	return (new_node);
}
