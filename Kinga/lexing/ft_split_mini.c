/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:19:40 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/09 16:31:44 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_token(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (s[i] == '$')
			{
				i++;
				count++;
			}
			else
				count++;
			while ((s[i]) && (s[i] != c))
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	**free_token(char **result, size_t token_index)
{
	while (token_index > 0)
		free(result[--token_index]);
	free(result);
	return (NULL);
}

static size_t	find_token_end(const char *s, size_t start, char delimiter)
{
	char	quote;
	size_t	end;

	quote = 0;
	end = start;
	while (s[end] && (quote || s[end] != delimiter))
	{
		if (s[end] == '\'' || s[end] == '\"')
		{
			if (quote == 0)
				quote = s[end];
			else if (quote == s[end])
				quote = 0;
		}
		else if (s[end] == '$' && quote != '\'')
			break ;
		end++;
	}
	return (end);
}

static char	**tk(const char *s, char c, char **result)
{
	size_t	token_index;
	size_t	start;
	size_t	end;

	start = 0;
	token_index = 0;
	while (s[start])
	{
		while (s[start] && s[start] == c)
			start++;
		if (s[start] == '\0')
			break ;
		if (s[start] == '$')
		{
			end = start + 1;
			result[token_index] = ft_substr(s, start, end - start);
			token_index += 1;
			start = end;
		}
		else
			end = find_token_end(s, start, c);
		result[token_index] = ft_substr(s, start, end - start);
		if (!result[token_index])
			return (free_token(result, token_index));
		token_index++;
		start = end;
	}
	result[token_index] = NULL;
	return (result);
}

char	**ft_split_mini(char const *s, char c)
{
	size_t	token_count;
	char	**result;

	if (!s)
		return (NULL);
	token_count = count_token(s, c);
	result = malloc((token_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (tk(s, c, result));
}
//✅ Co musisz zrobić (logika, nie kod):
//Jeśli natrafisz na $, to:

//dodaj token z $

//od razu policz drugi token z nazwą zmiennej, np. USER, ale tylko do pierwszego separatora / końca zmiennej

//Czyli $USER powinno dać dwa tokeny: "$" i "USER"

//Po dodaniu $ i USER, nie wywołuj potem jeszcze raz find_token_end, bo już to przeszłaś.

//✳️ Co jeszcze warto poprawić:
//Twój count_token() zlicza tylko raz $, ale nie osobno $ i USER → to też trzeba poprawić, bo masz teraz count < real_tokens.

//Cudzysłowy " i ' nie powinny być osobnymi tokenami – teraz niestety tak się dzieje.

