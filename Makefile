# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/01 19:22:14 by kdyga             #+#    #+#              #
#    Updated: 2025/07/14 13:11:04 by kikwasni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mini

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I minishell/ -I libft/includes
LDFLAGS = -lreadline libft/libft.a

SRCS = main/main.c Kamil/command/cd.c Kinga/read_line.c Kinga/lexing/clear_split.c Kinga/lexing/ft_split_mini.c Kinga/checkers/check1.c Kinga/checkers/check2.c
OBJS = $(SRCS:.c=.o)

# Libft
LIBFT_DIR = libft
LIBFT_NAME = libft.a

.PHONY: all clean fclean re valgrind libft

all: libft $(NAME)

$(NAME): $(OBJS) libft/$(LIBFT_NAME)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libft:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

valgrind: $(NAME)
	valgrind --leak-check=full --suppressions=readline.supp ./$(NAME)