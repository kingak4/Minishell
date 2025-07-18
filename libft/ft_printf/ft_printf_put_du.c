/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put_du.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:16:22 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/16 14:49:58 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_nbrlen(long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

int	pf_putnbr_prewid(long n, struct s_flgs *flags)
{
	int	printed;
	int	padding;
	int	count;

	count = flags->precision - pf_nbrlen(n);
	padding = calculate_padding(flags->width, flags->precision, n);
	printed = padding + count + pf_nbrlen(n);
	if (flags->minus == 0)
		handle_padding(padding, flags, 0);
	handle_sign_and_precision(&n, count, flags);
	pf_putnbr(flags, n);
	if (flags->minus == 1)
		handle_padding(padding, flags, 1);
	return (printed);
}

int	pf_putnbr_wid(long n, struct s_flgs *flags)
{
	int		printed;
	int		padding;

	printed = 0;
	padding = flags->width - pf_nbrlen(n);
	while (flags->minus == 0 && padding-- > 0)
	{
		buf_write(flags->buffer, ' ', &flags->index);
		printed++;
	}
	printed += pf_putnbr(flags, n);
	while (flags->minus == 1 && padding-- > 0)
	{
		buf_write(flags->buffer, ' ', &flags->index);
		printed++;
	}
	return (printed);
}

int	pf_putnbr_pre(long n, struct s_flgs *flags)
{
	int		printed;
	int		count;

	printed = 0;
	if (flags->dot == 1)
		count = flags->precision;
	else
		count = flags->width;
	if (n < 0 && flags->dot == 1)
		count -= pf_nbrlen(n) - 1;
	else
		count -= pf_nbrlen(n);
	if (n < 0)
	{
		buf_write(flags->buffer, '-', &flags->index);
		n = -n;
		printed++;
	}
	while (count-- > 0)
	{
		buf_write(flags->buffer, '0', &flags->index);
		printed++;
	}
	printed += pf_putnbr(flags, n);
	return (printed);
}

int	pf_putnbr(struct s_flgs *flags, long n)
{
	char	c;
	int		printed;

	printed = 0;
	if (n < 0)
	{
		buf_write(flags->buffer, '-', &flags->index);
		printed++;
		n = -n;
	}
	if (n / 10 > 0)
		printed += pf_putnbr(flags, n / 10);
	c = n % 10 + '0';
	buf_write(flags->buffer, c, &flags->index);
	printed++;
	return (printed);
}
