/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:43:41 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/24 00:24:45 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_s(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

// quote = 0;
char	*m_rest(const char *s, int i, char *rest, int len)
{
	int		j;
	char	quote;

	j = 0;
	while (i <= len)
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (quote == 0)
				quote = s[i];
			else if (quote == s[i])
				quote = 0;
			rest[j++] = s[i++];
		}
		else if (is_s(s[i]) && !quote)
		{
			rest[j++] = ' ';
			while (i <= len && is_s(s[i]))
				i++;
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
