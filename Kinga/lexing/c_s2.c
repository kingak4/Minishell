/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_s2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:24:10 by kikwasni          #+#    #+#             */
/*   Updated: 2025/07/09 12:39:21 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_check(char *str)
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
		return (0);
	}
	return (1);
}
