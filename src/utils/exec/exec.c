/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:51:39 by hsarraj           #+#    #+#             */
/*   Updated: 2025/01/10 10:51:39 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_builtin(t_cmd *cmd, t_env **envs)
{
	t_builtin	builtin[7];
	size_t		j;

	builtin[0] = (t_builtin){.name = "cd", .func = builtin_cd};
	builtin[1] = (t_builtin){.name = "echo", .func = builtin_echo};
	builtin[2] = (t_builtin){.name = "env", .func = builtin_env};
	builtin[3] = (t_builtin){.name = "exit", .func = builtin_exit};
	builtin[4] = (t_builtin){.name = "export", .func = builtin_export};
	builtin[5] = (t_builtin){.name = "pwd", .func = builtin_pwd};
	builtin[6] = (t_builtin){.name = "unset", .func = builtin_unset};
	j = 0;
	while (j < 7)
	{
		if(ft_strcmp(builtin[j].name, cmd->name) == 0)
			return(builtin[j].fun(cmd, envs));
		j++;
	}
	return(BUILTIN_NOT_FOUND);
}

static int	handle_errors(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (error(path, strerror(errno)), EXIT_FAILURE);
	if (S_ISDIR(sb.st_mode))
		return (error(path, "Is a directory"), 126);
	else if (access(path, X_OK) != 0)
		return (error(path, "Permission denied"), 126);
	return (EXIT_SUCCESS);
}

int exec_relative(t_cmd *cmd, t_env **envs)
{
	char	*path;
	int		error_code;
	char 	**envp;
	size_t	i;

	if(!cmd->name[0])
		return (EXIT_SUCCESS);
	path = resolve_path(cmd->name, *envs, F_ok);
	if(!path)
		return(error(cmd->name, "command not found"), 127);
	error_code = handle_errors(path);
	if (error_code != EXIT_SUCCESS)
		return (free(path), error_code);
	envp = format_env(*envs);
	execve(path, cmd->args, envp);
	free(path);
	i = 0;
	while(envp[i])
		free(envp[i++]);
	free(envp);
	return (EXIT_FAILURE);
}

int exec_cmd (t_cmd *cmds, t_env **envs)
{
	int backups[2];
	int	exit_status;

	if(cmds->next)
		return(pipeline(cmds, envs));
	backups[0] = dup(STDIN_FILENO);
	backups[1] = dup(STDOUT_FILENO);
	redirs(cmds);
	exit_status = exec_builtin(cmds, envs);
	dup2(backups[0], STDIN_FILENO);
	dup2(backups[1], STDOUT_FILENO);
	close(backups[0]);
	close(backups[1]);
	if (exit_status == BUILTIN_NOT_FOUND)
		return (pipeline(cmds, envs));
	close_redirs(cmds);
	return (exit_status);
}
