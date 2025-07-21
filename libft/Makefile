# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/09 19:41:14 by kdyga             #+#    #+#              #
#    Updated: 2025/07/20 21:44:14 by kdyga            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = clang

CFLAGS = -Wall -Wextra -Werror -I includes/

HEADER = $(addsuffix .h, $(addprefix includes/, libutils get_next_line ft_printf))

FTIS = alnum alpha ascii count digit in print space spacenl where

FTSKIP = space spacenl char chars

FTMATH = abs nbrlen hexlen baselen power

FTMEM = bzero calloc memccpy memchr memcmp memcpy memdel memmove memset

FTPUT = char endl nbr str char_fd endl_fd nbr_fd str_fd

FTSTR = chr cmp dup isnum join lcat lcpy len mapi ncmp nstr rchr trim helpers

FTSUB = ft_str/ft_substr ft_str/ft_split

FTTO = tolower toupper atoi itoa

FTEX = get_next_line/get_next_line printf/ft_printf get_next_line/get_next_line_helpers

FTPRF = flagger branch_csp branch_duxo put_c put_s put_du put_o put_x put_p helpers helperscd

SRC = $(addsuffix .c, $(addprefix ft_is/ft_is, $(FTIS))) \
	$(addsuffix .c, $(addprefix ft_math/ft_, $(FTMATH))) \
	$(addsuffix .c, $(addprefix ft_mem/ft_, $(FTMEM))) \
	$(addsuffix .c, $(addprefix ft_put/ft_put, $(FTPUT))) \
	$(addsuffix .c, $(addprefix ft_skip/ft_skip_, $(FTSKIP))) \
	$(addsuffix .c, $(addprefix ft_str/ft_str, $(FTSTR)) $(FTSUB)) \
	$(addsuffix .c, $(addprefix ft_to/ft_, $(FTTO))) \
	$(addsuffix .c, $(addprefix ft_, $(FTEX))) \
	$(addsuffix .c, $(addprefix ft_printf/ft_printf_, $(FTPRF))) \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Libft: Creating library $(NAME)..."
	@$(AR) rcs $@ $^
	@echo "Libft: Library $(NAME) created successfully."

%.o: %.c
	@echo "Libft: Compiling $< into $@..."
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "Libft: Removing object files..."
	@rm -f $(OBJ)
	@echo "Libft: Object files removed."

fclean: clean
	@echo "Libft: Removing library $(NAME)..."
	@rm -f $(NAME)
	@echo "Libft: Library $(NAME) removed."

re: fclean all

norm:
	norminette $(SRC) $(HEADER)

.PHONY: all clean fclean re norm