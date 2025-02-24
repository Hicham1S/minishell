/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:06:52 by hsarraj           #+#    #+#             */
/*   Updated: 2025/01/21 15:06:52 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	error_invalid(char *path, t_env **envs)
{
	struct stat	sb;

	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	if (stat(path, &sb) == -1)
	{
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		set_stat(envs, 1);
	}
	else if (!S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
		set_stat(envs, 1);
	}
	else
		ft_putstr_fd(": Unknown error\n", STDERR_FILENO);
}

static	char	*home_path(t_env **envs)
{
	t_env	*env;

	env = get_env(*envs, "HOME");
	if (!env)
	{
		set_stat(envs, 1);
		return (error("cd", "HOME not set"), NULL);
	}
	return (env->value);
}

static	char	*get_path(t_cmd *cmd, t_env **envs)
{
	size_t	i;
	char	*path;
	char	*home;

	i = 1;
	path = NULL;
	while (cmd->args[i])
	{
		if (cmd->args[i][0])
		{
			if (path)
				return (set_stat(envs, 1), error("cd",
						"too many arguments"), NULL);
			path = cmd->args[i];
		}
		i++;
	}
	if (!path)
	{
		home = home_path(envs);
		if (home)
			return (ft_strdup(home));
		return (NULL);
	}
	return (ft_strdup(path));
}

static	void	tilted_path(t_env **envs, char **path)
{
	char	*home;
	char	*tmp;

	home = home_path(envs);
	if (home)
	{
		tmp = ft_strjoin(home, *path + 1);
		free(*path);
		*path = tmp;
	}
}

int	builtin_cd(t_cmd *cmd, t_env **envs)
{
	char	*path;
	char	current[1024];

	path = get_path(cmd, envs);
	if (path && path[0] == '~')
		tilted_path(envs, &path);
	if (!path)
		return (EXIT_FAILURE);
	if (path[0])
	{
		if (chdir(path) == -1)
		{
			error_invalid(path, envs);
			return (free(path), EXIT_FAILURE);
		}
		if (getcwd(current, 1024))
			set_env(envs, "PWD", current);
	}
	if (path)
		free(path);
	set_stat(envs, 0);
	return (EXIT_SUCCESS);
}
