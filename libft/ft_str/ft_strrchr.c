/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 19:24:30 by kdyga             #+#    #+#             */
/*   Updated: 2024/03/14 17:35:06 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;
	char	cc;

	res = NULL;
	cc = (char)c;
	while (*s)
	{
		if (*s == cc)
			res = (char *)s;
		s++;
	}
	if (cc == '\0')
		return ((char *)s);
	return (res);
}
