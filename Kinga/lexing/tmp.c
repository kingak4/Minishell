#include "minishell.h"
#include <ctype.h>
#include <string.h>

int	ft_isalnum(int c)
{
	return (isalnum(c));
}

static int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

//static char	**free_token(char **result, size_t token_index)
//{
//	while (token_index > 0)
//		free(result[--token_index]);
//	free(result);
//	return (NULL);
//}

static char	**tk(const char *s, char c, char **result)
{
	size_t	token_index = 0;
	size_t	i = 0;

	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;

		if (s[i] == '\'')
		{
			size_t start = ++i;
			while (s[i] && s[i] != '\'')
				i++;
			result[token_index++] = ft_substr(s, start, i - start);
			if (s[i] == '\'')
				i++;
		}
		else if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
			{
				if (s[i] == '$')
				{
					result[token_index++] = ft_substr(s, i, 1);
					i++;
					size_t var_start = i;
					while (is_var_char(s[i]))
						i++;
					if (i > var_start)
						result[token_index++] = ft_substr(s, var_start, i - var_start);
				}
				else
				{
					size_t word_start = i;
					while (s[i] && s[i] != '$' && s[i] != '"')
						i++;
					result[token_index++] = ft_substr(s, word_start, i - word_start);
				}
			}
			if (s[i] == '"')
				i++;
		}
		else if (s[i] == '$')
		{
			result[token_index++] = ft_substr(s, i, 1);
			i++;
			size_t var_start = i;
			while (is_var_char(s[i]))
				i++;
			if (i > var_start)
				result[token_index++] = ft_substr(s, var_start, i - var_start);
		}
		else
		{
			size_t start = i;
			while (s[i] && s[i] != c && s[i] != '$' && s[i] != '"' && s[i] != '\'')
				i++;
			result[token_index++] = ft_substr(s, start, i - start);
		}
	}
	result[token_index] = NULL;
	return (result);
}

char	**ft_split_mini(const char *s, char c)
{
	size_t	count = 0;
	size_t	i = 0;
	char	**result;

	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		count++;
		if (s[i] == '"' || s[i] == '\'')
		{
			char quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			if (s[i] == quote)
				i++;
		}
		else
		{
			while (s[i] && s[i] != c)
			{
				if (s[i] == '$')
					i++;
				while (s[i] && s[i] != c && s[i] != '$' && s[i] != '"' && s[i] != '\'')
					i++;
			}
		}
	}
	result = malloc((count + 10) * sizeof(char *)); 
	if (!result)
		return (NULL);
	return (tk(s, c, result));
}