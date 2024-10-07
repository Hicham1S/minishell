// #include "../env/env.h"
// #include "../main/main.h"

// int ft_pwd(t_minishell *shell)
// {
// 	if (shell->pwd)
// 	{
// 		ft_printf("%s\n", shell->pwd);
// 		return (0);
// 	}
// 	else
// 	{
// 		ft_printf("pwd: error retrieving current directory\n");
// 		return (1);
// 	}
// }

// int update_oldpwd(t_minishell *shell, char *oldpath)
// {
// 	char *fullstr;

// 	if (oldpath)
// 	{
// 		fullstr = ft_strjoin("OLDPWD=", oldpath);
// 		if (fullstr)
// 		{
// 			register_env_exp(fullstr, shell->our_env, shell->our_exp);
// 			free(fullstr);
// 			return (0);
// 		}
// 		return (1);
// 	}
// 	return (1);
// }

// int update_pwd(t_minishell *shell, char *path)
// {
// 	char *fullstr;
// 	char *pwd;

// 	if (path)
// 	{
// 		fullstr = ft_strjoin("PWD=", path);
// 		if (fullstr)
// 		{
// 			register_env_exp(fullstr, shell->our_env, shell->our_exp);
// 			free(fullstr);
// 			pwd = ft_strdup(path);
// 			free(shell->pwd);
// 			shell->pwd = pwd;
// 			return (0);
// 		}
// 		return (1);
// 	}
// 	return (1);
// }

// int	check_cd_errors(t_minishell *shell,char *path)
// {
// 	if (path[0] == '-')
// 	{
// 		if (ft_strlen(path) == 1)
// 			ft_printf("bash: cd: -: invalid option\n");
// 		else
// 			ft_printf("bash: cd: -%c: invalid option\n", path[1]);
// 		return (2);
// 	}
// 	// if (!get_env_clone("HOME", shell->our_env))
// 	// 	return (ragequit("bash: cd: HOME not set\n", 1));
// 	return (0);
// }

// int do_cd(t_minishell *shell, char *path)
// {
// 	char	*oldpath;
// 	char	*newpath;
// 	char	*target;

// 	oldpath = shell->pwd;
// 	if (check_cd_errors(shell, path))
// 	{
// 		newpath = getcwd(NULL, 0);
// 		if (newpath == NULL)
// 		{
// 			ft_printf("chdir: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
// 			return (1);
// 		}
// 		update_oldpwd(shell, oldpath);
// 		update_pwd(shell, newpath);    
// 		return (free(oldpath), free(newpath), free(path), 0);
// 	}
// 	else
// 	{
// 		ft_printf("bash: cd: %s: No such file or directory", path);
// 		return (1);
// 	}
// }
