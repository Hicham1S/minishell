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

static char	*get_oldpwd_path(t_env **envs)
{
	t_env	*oldpwd_env;

	oldpwd_env = get_env(*envs, "OLDPWD");
	if (!oldpwd_env || !oldpwd_env->value)
	{
		error("cd", "OLDPWD not set");
		return (NULL);
	}
	return (ft_strdup(oldpwd_env->value));
}

static void	update_pwd_oldpwd(t_env **envs, char *oldpwd)
{
	char	current[1024];

	if (getcwd(current, sizeof(current)))
	{
		set_env(envs, "PWD", current);
		set_env(envs, "OLDPWD", oldpwd);
	}
	else
		set_env(envs, "OLDPWD", oldpwd);
}

static int	change_directory(char *path, t_env **envs, char *oldpwd)
{
	int		cd_status;
	int		lost_dir;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	lost_dir = (cwd == NULL);
	free(cwd);
	cd_status = chdir(path);
	if (cd_status == -1)
	{
		error_invalid_cd(path, envs);
		free(path);
		set_stat(envs, 1);
		return (EXIT_FAILURE);
	}
	free(path);
	if (lost_dir)
		error("cd", "error retrieving current directory: getcwd failed");
	update_pwd_oldpwd(envs, oldpwd);
	set_stat(envs, 0);
	return (EXIT_SUCCESS);
}

int	builtin_cd(t_cmd *cmd, t_env **envs)
{
	char	*path;
	char	oldpwd[1024];

	if (!getcwd(oldpwd, sizeof(oldpwd)))
		oldpwd[0] = '\0';
	if (cmd->args[1] && ft_strcmp(cmd->args[1], "-") == 0)
	{
		path = get_oldpwd_path(envs);
		if (!path)
			return (set_stat(envs, 1), EXIT_FAILURE);
	}
	else
	{
		path = get_path(cmd, envs);
		if (!path)
			return (set_stat(envs, 1), EXIT_FAILURE);
		if (path[0] == '~')
			tilted_path(envs, &path);
	}
	return (change_directory(path, envs, oldpwd));
}
