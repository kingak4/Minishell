/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 11:32:21 by kdyga             #+#    #+#             */
/*   Updated: 2024/03/14 17:16:28 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	to_trim(const char *set, char c);
static char	*new_str(const char *s1, size_t start, size_t end);

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*ptr;

	total_size = count * size;
	ptr = malloc(total_size);
	if (ptr)
		ft_memset(ptr, 0, total_size);
	return (ptr);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	int		j;
	size_t	len;

	if (!s1 || !set)
		return (ft_strdup("(null)"));
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && to_trim(set, s1[i]))
		i++;
	while (j > i && to_trim(set, s1[j]))
		j--;
	len = 0;
	if (j >= i)
		len = j - i + 1;
	return (new_str(s1, i, len));
}

static char	*new_str(const char *s1, size_t start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (len == 0)
		return (ft_strdup(""));
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s1[start + i];
		i++;
	}
	return (str);
}

static int	to_trim(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
