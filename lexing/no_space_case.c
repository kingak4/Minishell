/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_space_case.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:36:04 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/23 11:53:19 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	update_quote(char c, char quote)
{
	if (c == '\"' || c == '\'')
	{
		if (quote == 0)
			return (c);
		else if (quote == c)
			return (0);
	}
	return (quote);
}

int	is_meta(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

static char	*wapper(const char *s, char *rest, int *i, int *j)
{
	if (*j > 0 && rest[*j - 1] != ' ')
		rest[(*j)++] = ' ';
	rest[(*j)++] = s[*i];
	if ((s[*i] == '>' && s[*i + 1] == '>')
		|| (s[*i] == '<' && s[*i + 1] == '<'))
		rest[(*j)++] = s[++(*i)];
	if (s[*i + 1] && s[*i + 1] != ' ')
		rest[(*j)++] = ' ';
	return (rest);
}

char	*normalize_input(const char *s, int i, int j, char quote)
{
	char	*rest;

	if (!s)
		return (NULL);
	rest = malloc(ft_strlen(s) * 3 + 1);
	if (!rest)
		return (NULL);
	while (s[i])
	{
		quote = update_quote(s[i], quote);
		if (!quote && is_meta(s[i]))
			rest = wapper(s, rest, &i, &j);
		else
			rest[j++] = s[i];
		i++;
	}
	rest[j] = '\0';
	return (rest);
}
