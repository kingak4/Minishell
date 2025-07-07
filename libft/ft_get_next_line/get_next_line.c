/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:21:58 by kdyga             #+#    #+#             */
/*   Updated: 2025/05/09 18:22:24 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	newline_check(char *stock, int read_size)
{
	int	i;

	i = 0;
	if (read_size == 0 && stock[0] == '\0')
		return (2);
	if (read_size == 0 || stock == NULL)
		return (0);
	while (stock[i] != '\0')
	{
		if (stock[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*buf_join(char *stock, char *buf)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (stock != NULL && stock[i] != '\0')
		i++;
	while (buf[j] != '\0')
		j++;
	new = malloc(sizeof(char) * (i + j + 1));
	if (!(new))
		return (ft_memdel(stock));
	i = 0;
	j = 0;
	while (stock != NULL && stock[i] != '\0')
		new[i++] = stock[j++];
	j = 0;
	while (buf[j] != '\0')
		new[i++] = buf[j++];
	new[i] = '\0';
	if (stock != NULL)
		ft_memdel(stock);
	return (new);
}

char	*stock_trim(char *stock)
{
	int		i;
	int		j;
	char	*trimmed;

	i = 0;
	j = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	while (stock[i++] != '\0')
		j++;
	trimmed = malloc(sizeof(char) * j + 1);
	if (!(trimmed))
		return (ft_memdel(stock));
	i = 0;
	j = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	if (stock[i] == '\0')
		i--;
	i++;
	while (stock[i] != '\0')
		trimmed[j++] = stock[i++];
	trimmed[j] = '\0';
	ft_memdel(stock);
	return (trimmed);
}

char	*get_line(char *stock)
{
	int		i;
	char	*line;

	i = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	line = malloc(sizeof(char) * i + 1);
	if (!(line))
		return (ft_memdel(stock));
	i = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
	{
		line[i] = stock[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

int	get_next_line(int fd, char **line)
{
	int			read_len;
	char		buf[BUFFER_SIZE + 1];
	static char	*stock = NULL;

	if (handle_read_error(fd, line, buf) == -1)
		return (-1);
	read_len = 1;
	while (!newline_check(stock, read_len))
	{
		read_len = process_buffer(fd, &stock, buf);
		if (read_len == -1)
			return (-1);
	}
	if (handle_newline_check(line, &stock, read_len) != 0)
		return (-1);
	if (read_len != 0)
		return (1);
	else
		return (0);
}
