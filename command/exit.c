/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 22:56:32 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/20 22:09:11 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit(char **args, t_mini *shell)
{
    int code = shell->last_exit_code;
    if (args[1])
        code = atoi(args[1]);
    exit(code);
}