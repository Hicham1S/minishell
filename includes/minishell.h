#ifndef MINISHELL_H
# define MINISHELL_H

# include "types.h"
# include "builtins.h"
# include "../libft/libft.h"
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

void	redirs(t_cmd *cmd);


#endif