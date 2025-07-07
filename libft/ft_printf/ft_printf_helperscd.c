/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helperscd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:14:48 by kdyga             #+#    #+#             */
/*   Updated: 2025/05/09 19:15:25 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_sign_and_precision(long *n, int count, struct s_flgs *flags)
{
	if (*n < 0)
	{
		buf_write(flags->buffer, '-', &flags->index);
		*n = -*n;
	}
	while (count-- > 0)
		buf_write(flags->buffer, '0', &flags->index);
}

int	calculate_padding(int width, int precision, long n)
{
	int	count;
	int	padding;

	count = precision - pf_nbrlen(n);
	if (n < 0)
		count += 1;
	if (count <= 0)
		count = 0;
	padding = width - pf_nbrlen(n) - count;
	if (padding <= 0)
		padding = 0;
	return (padding);
}
