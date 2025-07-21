/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:22:20 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/21 20:34:34 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_double_array(char **arr)
{
    int i;

    if (!arr)
        return;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

char *get_env_value(const char *key, char **envp)
{
    int i;
    int len;

    if (!key || !envp)
        return (NULL);
    len = strlen(key);
    i = 0;
    while (envp[i])
    {
        // porównaj do "KEY=" na początku stringa
        if (strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
            return (envp[i] + len + 1);  // zwróć wskaźnik na wartość
        i++;
    }
    return (NULL);
}
void executor(t_two *cmd, t_mini *shell)
{
    if (is_builtin(cmd->cmd))
        exec_builtin(cmd->args, shell);
    else
        exec_external(cmd->args, shell->envp);
}

static char *join_path_cmd(const char *path, const char *cmd)
{
    char *full_path;
    int len;

    len = strlen(path) + strlen(cmd) + 2;
    full_path = malloc(len);
    if (!full_path)
        return (NULL);
    snprintf(full_path, len, "%s/%s", path, cmd);
    return (full_path);
}

char *find_cmd_path(const char *cmd, char **envp)
{
    char **paths;
    char *path_env;
    char *full_path;
    int i;

    if (!cmd || !envp)
        return (NULL);
    path_env = get_env_value("PATH", envp);
    if (!path_env)
        return (NULL);
    paths = ft_split(path_env, ':');  // zakładamy, że masz ft_split
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i])
    {
        full_path = join_path_cmd(paths[i], cmd);
        if (!full_path)
            break ;
        if (access(full_path, X_OK) == 0)
        {
            free_double_array(paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    free_double_array(paths);
    return (NULL);
}