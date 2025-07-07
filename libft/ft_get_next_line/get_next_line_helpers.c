/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:22:58 by kdyga             #+#    #+#             */
/*   Updated: 2025/05/09 18:23:18 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	handle_read_error(int fd, char **line, char *buf)
{
	if (line == NULL || fd < 0 || BUFFER_SIZE < 1 || (read(fd, buf, 0)) < 0)
		return (-1);
	return (0);
}

int	process_buffer(int fd, char **stock, char *buf)
{
	int	read_len;

	read_len = read(fd, buf, BUFFER_SIZE);
	if (read_len == -1)
		return (-1);
	buf[read_len] = '\0';
	if (read_len == 0 || buf[read_len - 1] != '\n')
		ft_printf("  \b\b");
	*stock = buf_join(*stock, buf);
	if (*stock == NULL)
		return (-1);
	return (read_len);
}

int	handle_newline_check(char **line, char **stock, int read_len)
{
	if (newline_check(*stock, read_len) == 2 && (*line == *stock))
		return (-2);
	*line = get_line(*stock);
	if (*line == NULL)
		return (-1);
	*stock = stock_trim(*stock);
	if (*stock)
		return (-1);
	ft_memdel(*stock);
	return (0);
}