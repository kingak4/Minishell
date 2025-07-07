# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/01 19:22:14 by kdyga             #+#    #+#              #
#    Updated: 2025/07/07 16:00:28 by kikwasni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I minishell/
LDFLAGS = -lreadline
NAME = mini

SRCS = main/main.c Kamil/command/cd.c Kinga/read_line.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re valgrind

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

valgrind: $(NAME)
	valgrind --leak-check=full --suppressions=readline.supp ./$(NAME)