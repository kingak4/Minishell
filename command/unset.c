/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 22:57:10 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/20 22:22:23 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **remove_env_var(char **envp, const char *var)
{
    int i = 0;
    int j = 0;
    int var_len = ft_strlen(var);
    int env_len = 0;

    while (envp[env_len])
        env_len++;

    char **new_env = malloc(sizeof(char *) * (env_len + 1));
    if (!new_env)
        return NULL;

    while (envp[i])
    {
        if (!(ft_strncmp(envp[i], var, var_len) == 0 && envp[i][var_len] == '='))
        {
            new_env[j] = envp[i];
            j++;
        }
        else
        {
            free(envp[i]);
        }
        i++;
    }
    new_env[j] = NULL;

    free(envp);
    return new_env;
}

int ft_unset(char **args, t_mini *shell)
{
    int i = 1;
    while (args[i])
    {
        shell->envp = remove_env_var(shell->envp, args[i]);
        i++;
    }
    return 0;
}