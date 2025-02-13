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

extern int g_exit_status;

void	redirs(t_cmd *cmd);
void	close_redirs(t_cmd *cmds);

//debug
void	print_tokens(t_token *token);
void	print_cmd(t_cmd *cmd);

// exec.c
int	exec_cmd	(t_cmd *cmds, t_env **envs);

// path.c
char    *resolve_path(char *file, t_env *envs, int key);

// pipeline.c
int pipeline(t_cmd *cmds, t_env **envs);

//error.c
void	error_heredoc(char *delimiter);

// process.c
int wait_processes(t_cmd *cmds);

// signal.c
void	heredoc_signal(int signal);
void	main_signal(int signal, t_cmd *cmd, t_env *envs);
void	init_signal(void);
void	handler_signal(int sig);
void	cmd_signal(int signal);


void	error(char *msg, char *more);
void	error_write(char *cmd);

int		main(int argc, char **argv, char **envp);

void increment_shlvl(t_env *new_env);
int	relaunch_minishell(t_env *env);

#endif