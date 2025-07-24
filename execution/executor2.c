/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdyga <kdyga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 00:58:16 by kdyga             #+#    #+#             */
/*   Updated: 2025/07/24 01:01:27 by kdyga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char	*loop_paths(char **paths, const char *cmd)
{
	int		i;
	char	*full_path;

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

char	*find_cmd_path(const char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;

	if (!cmd || !envp)
		return (NULL);
	path_env = get_env_value("PATH", envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (loop_paths(paths, cmd));
}
