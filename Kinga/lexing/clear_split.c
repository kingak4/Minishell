/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:43:41 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/08 16:38:11 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		quotes_check(char *str)
{
	int	i;
	int	flag;
	int	f;

	i = 0;
	flag = 0;
	f = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' && f == 0)
			flag = !flag;
		else if (str[i] == '\'' && flag == 0)
			f = !f;
		i++;
	}
	if (flag || f)
	{
		printf("syntax error: unclosed quote\n");
		return 0;
	}
	return (1);
}

static int	is_s(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}
char	*space(char *s)
{
	int		i = 0;
	int		len;
	char	quote = 0;
	int		start;
	char	*rest;
	int		j = 0;

	len = ft_strlen(s) - 1;
	while (is_s(s[i]))
		i++;
	start = i;
	while (len > start && is_s(s[len]))
		len--;
	rest = malloc(sizeof(char) * (len - start + 2));
	if (!rest)
		return (NULL);
	i = start;
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
