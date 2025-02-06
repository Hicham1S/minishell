#include "../../../includes/minishell.h"

void	increment_shlvl(t_env *new_env)
{
	t_env	*shlvl_env;
	int		shlvl_val;
	char	*new_value;

	shlvl_env = get_env(new_env, "SHLVL");
	if (!shlvl_env)
		shlvl_val = 1;
	else
		shlvl_val = ft_atoi(shlvl_env->value) + 1;
	
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
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int relaunch_minishell(t_env *env)
{
	char    **new_envp;
	t_env   *new_env;
	int     status;
	pid_t   pid;
	char    *argv[2];

	pid = fork();
	if (pid < 0)
		return (1);
	
	if (pid == 0)
	{
		new_envp = format_env(env);
		new_env = init_env(new_envp);
		increment_shlvl(new_env);
		free_arrstr(new_envp);
		new_envp = format_env(new_env);
		if (!new_envp)
			exit(1);
		argv[0] = "./minishell";
		argv[1] = NULL;
		execve("./minishell", argv, new_envp);
		free_arrstr(new_envp);
		free_env(new_env);
		exit(1);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}