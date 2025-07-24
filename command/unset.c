/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 22:57:10 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/24 00:41:55 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_env_len(char **envp)
{
	int	len;

	len = 0;
	while (envp[len])
		len++;
	return (len);
}

static int	is_matching_var(const char *env_entry, const char *var, int var_len)
{
	return (ft_strncmp(env_entry, var, var_len) == 0
		&& env_entry[var_len] == '=');
}

static void	copy_non_matching_vars(char **new_env, char **envp,
		const char *var, int var_len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if (!is_matching_var(envp[i], var, var_len))
			new_env[j++] = envp[i];
		else
			free(envp[i]);
		i++;
	}
	new_env[j] = NULL;
}

char	**remove_env_var(char **envp, const char *var)
{
	int		var_len;
	int		env_len;
	char	**new_env;

	var_len = ft_strlen(var);
	env_len = get_env_len(envp);
	new_env = malloc(sizeof(char *) * (env_len + 1));
	if (!new_env)
		return (NULL);
	copy_non_matching_vars(new_env, envp, var, var_len);
	free(envp);
	return (new_env);
}

int	ft_unset(char **args, t_mini *shell)
{
	int	i;

	i = 1;
	while (args[i])
	{
		shell->envp = remove_env_var(shell->envp, args[i]);
		i++;
	}
	return (0);
}
