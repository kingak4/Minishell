/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:14:56 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/07 23:31:54 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cd(char **args)
{
    const char *path;

    if (!args[1])
        path = getenv("HOME");
    else
        path = args[1];

    if (chdir(path) != 0)
        perror("cd");

    return 1;
}
