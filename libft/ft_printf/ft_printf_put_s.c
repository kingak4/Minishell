/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put_s.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:17:52 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/16 14:50:12 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	pf_putstr_prewid(char *s, struct s_flgs *flags)
{
	int		ssize;
	int		padsize;
	char	c;

	if (flags->zero == 1 && flags->minus == 0)
		c = '0';
	else
		c = ' ';
	ssize = calculate_ssize(s, flags);
	padsize = calculate_padsize(ssize, flags);
	if (flags->minus == 1)
		write_string_content(s, flags, ssize);
	write_padded_chars(c, padsize, flags);
	if (flags->minus == 0)
		write_string_content(s, flags, ssize);
	if (ssize > flags->width)
		return (ssize);
	else
		return (flags->width);
}

int	pf_putstr_wid(char *s, struct s_flgs *flags)
{
	int		padsize;
	int		i;
	char	c;

	c = ' ';
	if (flags->zero == 1 && flags->minus == 0)
		c = '0';
	if (flags->width > pf_strlen(s))
		padsize = flags->width - pf_strlen(s);
	else
		padsize = 0;
	i = 0;
	while (flags->minus == 1 && s[i] != '\0')
		buf_write(flags->buffer, s[i++], &flags->index);
	i = 0;
	while (i++ < padsize)
		buf_write(flags->buffer, c, &flags->index);
	i = 0;
	while (flags->minus == 0 && s[i] != '\0')
		buf_write(flags->buffer, s[i++], &flags->index);
	if (pf_strlen(s) > flags->width)
		return (pf_strlen(s));
	else
		return (flags->width);
}

int	pf_putstr_pre(struct s_flgs *flags, char *s, int prec)
{
	int	ssize;
	int	i;

	if (pf_strlen(s) < prec)
		ssize = pf_strlen(s);
	else
		ssize = prec;
	i = 0;
	while (i < ssize && s[i] != '\0')
		buf_write(flags->buffer, s[i++], &flags->index);
	return (ssize);
}

int	pf_putstr(struct s_flgs *flags, char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		buf_write(flags->buffer, s[i++], &flags->index);
	return (i);
}
