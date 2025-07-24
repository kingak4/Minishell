/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:04:35 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/24 16:52:46 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "minishell.h"
# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define MAX_INPUT 1024
# define MAX_ARGS 64
// r_in = 1 to jest > r_app = 1 >> lub  = 0 brak
// r_out = 1 to jest < r_hdoc = 1 << lub  = 0 brak
// falgi dodaj do komend aby było razem 
typedef struct s_redirect
{
	int		r_in;
	int		r_out;
	int		r_app;
	int		r_hdoc;
}		t_redirect;

typedef struct s_pars
{
	struct s_pars	*next;
	char			*line;
	char			**tokens;
	char			*cmd;
	char			**file;
	char			**flags;
	int				var;
	char			**args;
	char			*str;
	int				pip;
	t_redirect		*redirect;
}		t_pars;

//Command
int		ft_echo(char **args);
int		ft_cd(char **args);
int		ft_pwd(void);
int		ft_env(void);
int		ft_export(char **args);
int		ft_unset(char **args);
void	ft_exit(char **args);

// parsing
t_pars	*read_cmd(t_pars *read);
t_pars	*check_read(t_pars *read);
int		quotes_check(char *str);
char	**ft_split_mini(char const *s, char c);
char	*space(const char *s);
char	*remove_hyphens(char *s);
int		is_empty_line(t_pars *read);
void	free_list(t_pars *read);
int		check_redirect_error(t_pars *read, int i);
int		is_pipe_first(t_pars *read);
int		is_pipe_last(t_pars *read);
int		is_double_pipe(t_pars *read, int i);
int		is_redi_and_pipe(t_pars *read, int i, int len);
int		is_redi1_last(t_pars *read);
int		is_double_redi1(t_pars *read, int i, char first);
int		is_semicolon(t_pars *read);
int		is_operator(t_pars *read);
t_pars	*lex(t_pars *read);
int		is_pipe(t_pars *read);
t_pars	*new_node(t_pars *read);
void	is_redi(t_pars *read);
char	**free_token(char **result, size_t token_index);
void	free_tab(char **splited);
t_pars	*init_pars(t_pars *read);
void	free_pars(t_pars *read);
int		check_flag(t_pars *read);
int		find_operator(t_pars *read, char *op, int start);
int		check_ops_with_spaces(t_pars *read, int i);
int		check_operator_spaces(t_pars *read, int pos, int op_len);
void	add_spaces_around_operators(t_pars *read);
char	*insert_spaces(char *line, int pos, int mask, int op_len);
int		is_meta(char c);
char	*normalize_input(const char *s, int i, int j, char quote);
int		flag_checker(t_pars *read);
t_pars	*flag_pars(t_pars *read);
char	quote_is_g(char c, char quote);
int		dolar_checker(t_pars *read);
t_pars	*dolar_pars(t_pars *read);
void	set_interactive_signals(void);
void	deactivate_ctrlc(int sig);
void	activate_ctrlc(int sig);
#endif
