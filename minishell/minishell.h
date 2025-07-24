/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:04:35 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/24 00:24:05 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_INPUT 255
# define MAX_ARGS 64
# define TRUNC 1
# define APPEND 2
# define INPUT 3
# define INPUT_ECHO 4
# define PIPE 5
# define STDERR 2

typedef struct s_redirect
{
	int				in;
	int				out;
	char			*file;
}					t_redirect;

typedef struct s_pars
{
	struct s_pars	*next;
	char			*line;
	char			*cmd;
	char			*file;
	char			*flag;
	int				var;
	char			*str;
	int				pip;
	t_redirect		*redirect;
	char			**tokens;
}					t_pars;
typedef struct s_mini
{
	char			**envp;
	int				stdin_copy;
	int				stdout_copy;
	int				last_exit_code;
	int				pipe_read;
	int				pipe_write;
	int				output_file;
	int				no_file;
	int				ret;
	pid_t			pid;
	int				parent;
	int				last;
}					t_mini;

typedef struct s_two
{
	char			**args;
	char			*cmd;
	t_redirect		*redirect;
	int				pipe[2];
	int				index;
	struct s_two	*next;
	char			*str;
}					t_two;

// checkers
// check 1
int					is_empty_line(t_pars *read);
int					quotes_check(char *str);
void				free_list(t_pars *read);
int					check_redirect_error(t_pars *read, int i);
int					is_pipe_first(t_pars *read);

// check 2
int					is_pipe_last(t_pars *read);
int					is_double_pipe(t_pars *read, int i);
int					is_redi_and_pipe(t_pars *read, int i, int len);
int					is_redi1_last(t_pars *read);

// check 3
int					is_double_redi1(t_pars *read, int i, char first);
int					is_semicolon(t_pars *read);
int					is_operator(t_pars *read);
// Command
// cd
int					ft_cd(char **args);
// echo
int					ft_echo(char **args);
// env
int					ft_env(char **env);
// exit
void				ft_exit(char **args, t_mini *shell);
// export
int					ft_export(char **args);
// pwd
int					ft_pwd(void);
// unset
char				**remove_env_var(char **envp, const char *var);
int					ft_unset(char **args, t_mini *shell);

// Execution
// bulitin
int					is_builtin(const char *cmd);
int					exec_builtin(char **args, t_mini *shell);
// executor
void				executor(t_two *cmd, t_mini *shell);
void				free_double_array(char **arr);
char				*get_env_value(const char *key, char **envp);
char				*find_cmd_path(const char *cmd, char **envp);
// execve_cmd
void				exec_external(char **args, char **envp);
// fd_utils
void				save_fds(int *stdin_copy, int *stdout_copy);
void				restore_fds(int stdin_copy, int stdout_copy);
void				close_fds(int fd1, int fd2);
// redir
int					handle_redirections(t_redirect *redir);

// Lexing
// clear_split
char				*m_rest(const char *s, int i, char *rest, int len);
char				*space(const char *s);
char				*remove_hyphens(const char *s);
// ft_split_mini.c
char				**ft_split_mini(char const *s, char c);
// lex.c
t_pars				*lex(t_pars *read);
// read_line.c
t_pars				*read_cmd(t_pars *read);
t_pars				*check_read(t_pars *read);

// Main
// main
int					main(int argc, char **argv, char **envp);
void				execute(t_two **cmd, t_mini *shell);
// pipe
int					minipipe(t_mini *mini);
void				redir_pipe(t_mini *mini, t_two *token, int type);
void				check_file_redirections_pipe(t_mini *mini, t_two *token);
void				handle_pipe(t_mini *mini, t_two *token);
void				execute_pipeline(t_two *cmd, t_mini *mini);
void				input_pipe(t_mini *mini, t_two *token);
t_two				*find_prev_pipe(t_two *token, int skip);
t_two				*find_next_pipe(t_two *token, int skip);
int					is_type(t_two *token, int type);
void				process_pipe_segment(t_mini *mini, t_two *prev,
						t_two *token);
void				ft_close(int fd);
int					is_type(t_two *token, int type);
void				input_pipe(t_mini *mini, t_two *token);

// Parsing
// pars1
int					is_pipe(t_pars *read);
t_pars				*new_node(t_pars *read);
void				is_redi(t_pars *read);

#endif
