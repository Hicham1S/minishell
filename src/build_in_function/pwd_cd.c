#include "builtins.h"

int ft_pwd(t_minishell *shell)
{
	char	*pwd;

	pwd = get_env_clone("PWD", shell->our_env);
	if (pwd)
	{
		ft_printf("%s\n", pwd);
		return (0);
	}
	else
	{
		ft_printf("pwd: error retrieving current directory\n");
		return (1);
	}
}

int update_oldpwd(t_minishell *shell, char *oldpath)
{
	char *fullstr;

	if (oldpath)
	{
		fullstr = ft_strjoin("OLDPWD=", oldpath);
		if (fullstr)
		{
			register_env_exp(fullstr, shell->our_env, shell->our_exp);
			free(fullstr);
			return (0);
		}
		return (1);
	}
	return (1);
}

int update_pwd(t_minishell *shell, char *path)
{
	char *fullstr;

	if (path)
	{
		fullstr = ft_strjoin("PWD=", path);
		if (fullstr)
		{
			register_env_exp(fullstr, shell->our_env, shell->our_exp);
			free(fullstr);
			return (0);
		}
		return (1);
	}
	return (1);
}

int	check_cd_errors(char *path)
{
	if (path[0] == '-')
	{
		if (ft_strlen(path) == 1)
			ft_printf("bash: cd: -: invalid option\n");
		else
			ft_printf("bash: cd: -%c: invalid option\n", path[1]);
		return (2);
	}
	return (0);
}

int do_cd(t_minishell *shell, char *path)
{
	char	*oldpath;
	char	*newpath;

	oldpath = get_env_clone("PWD", shell->our_env);
	if (check_cd_errors(path))
		return (check_cd_errors(path));
	if (chdir(path) == 0)
	{
		newpath = getcwd(NULL, 0);
		if (newpath == NULL)
		{
			ft_printf("chdir: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
			return (1);
		}
		update_oldpwd(shell, oldpath);
		update_pwd(shell, newpath);    
		return (free(newpath), 0);
	}
	else
	{
		ft_printf("bash: cd: %s: No such file or directory\n", path);
		return (1);
	}
}

int	cd_noarg(t_minishell *shell)
{
	char	*HOME;

	HOME = get_env_clone("HOME", shell->our_env);
	if (HOME)
		return (do_cd(shell, HOME));
	else
		return (ragequit("bash: cd: HOME not set\n", 1));
}