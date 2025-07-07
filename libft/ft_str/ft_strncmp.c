/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:48:33 by kdyga             #+#    #+#             */
/*   Updated: 2024/03/12 19:10:19 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (!s1[i] && !s2[i])
			return (0);
		i++;
	}
	return (0);
}
/*
int main()
{
    const char *s1 = "Hello";
    const char *s2 = "Hell";
    int result = ft_strncmp(s1, s2, 4); // Porównujemy pierwsze 4 znaki
    if (result == 0)
        printf("s1 i s2 są identyczne na pierwszych 4 znakach.\n");
    else if (result < 0)
        printf("Pierwsze 4 znaki s1 są mniejsze niż pierwsze 4 znaki s2.\n");
    else
        printf("Pierwsze 4 znaki s1 są większe niż pierwsze 4 znaki s2.\n");

    return 0;
}*/
