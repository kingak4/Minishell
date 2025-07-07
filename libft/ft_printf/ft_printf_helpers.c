/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:13:49 by kdyga             #+#    #+#             */
/*   Updated: 2025/05/09 19:14:00 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	calculate_ssize(char *s, struct s_flgs *flags)
{
	if (pf_strlen(s) < flags->precision)
		return (pf_strlen(s));
	return (flags->precision);
}

int	calculate_padsize(int ssize, struct s_flgs *flags)
{
	if (flags->width > ssize)
		return (flags->width - ssize);
	return (0);
}

void	write_padded_chars(char c, int padsize, struct s_flgs *flags)
{
	int	i;

	i = 0;
	while (i++ < padsize)
		buf_write(flags->buffer, c, &flags->index);
}

void	write_string_content(char *s, struct s_flgs *flags, int ssize)
{
	int	i;

	i = 0;
	while (i < ssize && s[i] != '\0')
		buf_write(flags->buffer, s[i++], &flags->index);
}

void	handle_padding(int padding, struct s_flgs *flags, int is_left_aligned)
{
	while (padding-- > 0)
		buf_write(flags->buffer, ' ', &flags->index);
	if (!is_left_aligned)
		padding = 0;
}