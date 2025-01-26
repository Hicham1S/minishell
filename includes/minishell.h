#ifndef MINISHELL_H
# define MINISHELL_H

# include "types.h"
# include "builtins.h"
# include "../libft/libft.h"
#include "utils.h"
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
# include "../src/utils/tokens/tokens.h"
# include "../src/utils/command/command.h"

typedef struct s_minishell
{
	t_env	*envs;
}	t_minishell;

void	redirs(t_cmd *cmd);
void	close_redirs(t_cmd *cmds);

//debug
void	print_tokens(t_token *token);
void	print_cmd(t_cmd *cmd);

#endif