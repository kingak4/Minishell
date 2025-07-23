/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:51:17 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/22 09:35:01 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **splited)
{
	int	i;

	i = 0;
	while (splited[i] != NULL)
	{
		free(splited[i]);
		i++;
	}
	free(splited);
}

void	free_list(t_pars *read)
{
	t_pars	*current;
	t_pars	*next_node;

	if (read == NULL)
		return ;
	current = read;
	while (current != NULL)
	{
		next_node = current->next;
		free_pars(current);
		current = next_node;
	}
}

char	*remove_hyphens(const char *s)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	rest = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!rest)
		return (NULL);
	while (s[i])
	{
		if (s[i] != '"')
		{
			rest[j] = s[i];
			j++;
		}
		i++;
	}
	rest[j] = '\0';
	return (rest);
}
