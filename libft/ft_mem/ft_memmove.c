/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:47:56 by kdyga             #+#    #+#             */
/*   Updated: 2025/05/09 18:48:07 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

static void	copy_to_temp(unsigned char *temp,
	const unsigned char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		temp[i] = src[i];
		i++;
	}
}

static void	copy_from_temp(unsigned char *dst,
	const unsigned char *temp, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] = temp[i];
		i++;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p;
	unsigned char	*q;
	unsigned char	*temp;

	p = (unsigned char *)dst;
	q = (unsigned char *)src;
	temp = malloc(len);
	if (!temp)
		return (NULL);
	copy_to_temp(temp, q, len);
	copy_from_temp(p, temp, len);
	free(temp);
	return (dst);
}