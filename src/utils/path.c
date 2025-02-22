/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 08:31:59 by hsarraj           #+#    #+#             */
/*   Updated: 2025/02/01 08:31:59 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_path(char *path, char *file)
{
	char	*output;
	size_t	path_len;
	size_t	file_len;

	if (!path || !file)
		return (NULL);
	path_len = ft_strlen(path);
	if (path[path_len -1] == '/')
		path_len--;
	file_len = ft_strlen(file);
	if (file[0] == '/')
		file_len--;
	output = malloc(sizeof(char) * (path_len + file_len + 2));
	if (!output)
		return (NULL);
	ft_memcpy(output, path, path_len);
	output[path_len] = '/';
	ft_memcpy(output + path_len + 1, file, file_len);
	output[path_len + file_len + 1] = '\0';
	return (output);
}

static char	**get_path_dirs(t_env *envs)
{
	t_env	*path;

	path = get_env(envs, "PATH");
	if (!path)
		return (NULL);
	return (ft_split(path->value, ':'));
}

static char	*find_executable(char **paths, char *file, int key)
{
	size_t	i;
	char	*output;

	i = 0;
	while (paths[i])
	{
		output = join_path(paths[i], file);
		if (access(output, key) >= 0)
			return (output);
		free(output);
		free(paths[i]);
		i++;
	}
	return (NULL);
}

char	*resolve_path(char *file, t_env *envs, int key)
{
	char	**paths;
	char	*output;

	if (!file || !file[0])
		return (NULL);
	if (access(file, key) >= 0)
		return (ft_strdup(file));
	paths = get_path_dirs(envs);
	if (!paths)
		return (NULL);
	output = find_executable(paths, file, key);
	free(paths);
	return (output);
}
