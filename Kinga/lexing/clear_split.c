/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:43:41 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/21 15:00:36 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_s(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

static char	update_quote(char c, char quote)
{
	if ((c == '\'' || c == '\"'))
	{
		if (quote == 0)
			return (c);
		else if (quote == c)
			return (0);
	}
	return (quote);
}

static int	skip_spaces(const char *s, int i, int len)
{
	while (i <= len && is_s(s[i]))
		i++;
	return (i);
}

char	*m_rest(const char *s, int i, char *rest, int len)
{
	int		j;
	char	quote;

	j = 0;
	quote = 0;
	while (i <= len)
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = update_quote(s[i], quote);
			rest[j++] = s[i++];
		}
		else if (is_s(s[i]) && !quote)
		{
			rest[j++] = ' ';
			i = skip_spaces(s, i, len);
		}
		else
			rest[j++] = s[i++];
	}
	rest[j] = '\0';
	return (rest);
}

char	*space(const char *s)
{
	int		i;
	int		len;
	int		start;
	char	*rest;

	i = 0;
	len = ft_strlen(s) - 1;
	while (is_s(s[i]))
		i++;
	start = i;
	while (len > start && is_s(s[len]))
		len--;
	i = start;
	rest = malloc(sizeof(char) * (len - start + 2));
	if (!rest)
		return (NULL);
	rest = m_rest(s, i, rest, len);
	return (rest);
}
