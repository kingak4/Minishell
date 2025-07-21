# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/01 19:22:14 by kdyga             #+#    #+#              #
#    Updated: 2025/07/20 23:15:28 by kdyga            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I minishell/ -I libft/includes/
LDFLAGS = -lreadline -L libft 
NAME = mini
LIBFT = -lft
LDLIBS = -lreadline

CHECKERS = check1 check2 check3
COMMAND = cd echo env exit export pwd unset
EXECUTION = bulitin executor execve_cmd fd_utils redir
LEXING = clear_split ft_split_mini lex read_line
MAIN = main pipe
PARSING = pars1

OBJ_DIR = obj

SRC = $(addsuffix .c, $(addprefix checkers/, $(CHECKERS))) \
      $(addsuffix .c, $(addprefix command/, $(COMMAND))) \
      $(addsuffix .c, $(addprefix execution/, $(EXECUTION))) \
      $(addsuffix .c, $(addprefix lexing/, $(LEXING))) \
      $(addsuffix .c, $(addprefix main/, $(MAIN))) \
      $(addsuffix .c, $(addprefix parsing/, $(PARSING))) \

OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

.PHONY: all clean fclean re valgrind

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LDLIBS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C libft/
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C libft/
	@rm -f $(NAME)

re: fclean all

valgrind: $(NAME)
	valgrind --leak-check=full --suppressions=readline.supp ./$(NAME)

