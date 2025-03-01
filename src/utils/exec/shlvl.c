/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:15:02 by hsarraj           #+#    #+#             */
/*   Updated: 2025/02/07 13:15:02 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	increment_shlvl(t_env *new_env)
{
	t_env	*shlvl_env;
	int		shlvl_val;
	char	*new_value;

	shlvl_env = get_env(new_env, "SHLVL");
	if (shlvl_env)
		shlvl_val = ft_atoi(shlvl_env->value) + 1;
	else
		shlvl_val = 1;
	new_value = ft_itoa(shlvl_val);
	if (!new_value)
		return ;
	set_env(&new_env, "SHLVL", new_value);
	free(new_value);
}

void	free_arrstr(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static void	child_process(t_env *env)
{
	char	**new_envp;
	t_env	*new_env;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	new_env = init_env(format_env(env));
	if (!new_env)
		exit(1);
	increment_shlvl(new_env);
	new_envp = format_env(new_env);
	if (!new_envp)
		exit(1);
	execve("./minishell", (char *[]){"./minishell", NULL}, new_envp);
	perror("execve failed");
	free_arrstr(new_envp);
	free_env(new_env);
	exit(1);
}

int	relaunch_minishell(t_env *env)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		child_process(env);
	waitpid(pid, &status, 0);
	set_stat(&env, status >> 8);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	return (status >> 8);
}
