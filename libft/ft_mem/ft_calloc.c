/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:45:13 by kdyga             #+#    #+#             */
/*   Updated: 2025/05/09 18:45:15 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*space;
	size_t	i;

	i = 0;
	space = malloc(size * count + 1);
	if (!(space))
		return (NULL);
	while (i < count * size + 1)
		space[i++] = '\0';
	return (space);
}