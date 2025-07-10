/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:19:40 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/10 18:44:18 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		sig_quote(char *s)
{
	int	i;
	
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
			return (1);
		i++;
	}
	return(0);
}

int		dub_quote(char *s)
{
	int	i;
	int	flag;
	
	i = 0;
	flag = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"')
			flag = 1;
		i++;
	}
	return(flag);
}

char	*c_token_in_sig(char *s, size_t *i)
{
	size_t	start;
	size_t	end;
	
	if (s[*i] != '\'')
		return (NULL);
	(*i)++;
	start = *i;
	while(s[*i] && s[*i] != '\'')
		(*i)++;
	end = *i;
	if (s[*i] == '\'')
		(*i)++;
	return (ft_substr(s, start, end - start));
}
char	*token_dolar(char *s, size_t *i)
{
	size_t	start;

	if (s[*i] != '$')
		return (NULL);
	start = *i;
	(*i)++;
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
	if (start + 1 == *i)
		return (ft_strdup("$"));
	return (ft_substr(s, start, *i - start));
}

char	**tk(char *s, char c, char **rest)
{
	size_t	i;
	size_t	token_id;
	size_t	start;

	s = space(s);
	i = 0;
	token_id = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		if (s[i] == '\'')
			rest[token_id++] = c_token_in_sig(s, &i);
		else if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
			{
				if (s[i] == '$')
					rest[token_id++] = token_dolar(s, &i);
				else
				{
					start = i;
					while (s[i] && s[i] != '$' && s[i] != '"')
						i++;
					rest[token_id++] = ft_substr(s, start, i - start);
				}
			}
			if (s[i] == '"')
				i++;
		}
		else if (s[i] == '$')
			rest[token_id++] = token_dolar(s, &i);
		else
		{
			start = i;
			while (s[i] && s[i] != c && s[i] != '"' && s[i] != '\'' && s[i] != '$')
				i++;
			if (start < i)
				rest[token_id++] = ft_substr(s, start, i - start);
		}
	}
	rest[token_id] = NULL;
	return (rest);
}
char	**ft_split_mini(char const *s, char c)
{
	char	**rest;

	if (!s)
		return (NULL);
	rest = malloc((ft_strlen(s) + 1) * sizeof(char *));
	if (!rest)
		return (NULL);
	return (tk((char *)s, c, rest));
}
