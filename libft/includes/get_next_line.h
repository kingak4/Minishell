/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:39:36 by kdyga             #+#    #+#             */
/*   Updated: 2025/05/09 19:39:38 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

int		get_next_line(int fd, char **line);
char	*error(char *stock);
int		newline_check(char *stock, int read_size);
char	*buf_join(char *stock, char *buf);
char	*stock_trim(char *stock);
char	*get_line(char *stock);
#endif