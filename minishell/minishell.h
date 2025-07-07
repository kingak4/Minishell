/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:04:35 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/07 16:21:07 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"

// read_line
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64
// in = 1 to jest > in = 2 >> in = 0 brak
// out = 1 to jest < out = 2 << out  = 0 brak
typedef struct s_redirect
{
	int		in;
	int		out;
}		t_redirect;


typedef struct s_pars
{
	struct pars	*next;
	char		*line;
	char		*cmd;
	char		*file;
	char		*flag;
	int			var;
	char		*str;
	int			pip;
	t_redirect	*redirect;
}		t_pars;

//Command
int ft_echo(char **args);
int ft_cd(char **args);
int ft_pwd(void);
int ft_env(void);
int ft_export(char **args);
int ft_unset(char **args);
void ft_exit(char **args);

// parsing
t_pars *read_cmd(t_pars *read);

#endif
