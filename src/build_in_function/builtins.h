#ifndef BUILTIN_H
# define BUILTIN_H

# include "../shell/shell.h"

int ft_pwd(t_minishell *shell);
int update_oldpwd(t_minishell *shell, char *oldpath);
int update_pwd(t_minishell *shell, char *path);
int	check_cd_errors(char *path);
int do_cd(t_minishell *shell, char *path);
int	cd_noarg(t_minishell *shell);

#endif