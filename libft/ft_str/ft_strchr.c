/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:23:41 by kdyga             #+#    #+#             */
/*   Updated: 2024/03/02 19:07:56 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char)c;
	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *)&s[i]);
	return (NULL);
}
/*
int main() {
    const char *ptr_s = "Kamil";
    char search_char = 'K';
    int i = 0;

    // Wyszukiwanie znaku w ciągu znaków
    char *ptr_char = ft_strchr(ptr_s, search_char);

    if (ptr_char != NULL) {
        // Obliczanie indeksu znalezionego znaku
        i = ptr_char - ptr_s;
        printf("Znaleziono znak '%c' w ciągu: %s\n", search_char, ptr_s);
        printf("Tekst po znalezionym znaku: %s\n", ptr_char);
    } else {
        printf("Nie znaleziono znaku '%c' w ciągu: %s\n", search_char, ptr_s);
    }

    return 0;
}
*/
