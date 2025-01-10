#ifndef MINISHELL_H
# define MINISHELL_H

# include "types.h"
# include "utils.h"
# include "builtins.h"
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <string.h>

typedef struct s_minishell
{
	bool	force_exit;
	bool	heredoc;
	int		signal;
	t_env	*envs;
}	t_minishell;

extern t_minishell	g_minishell;

#endif