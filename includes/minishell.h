/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dawwad <dawwad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:52:57 by dawwad            #+#    #+#             */
/*   Updated: 2025/03/10 14:52:57 by dawwad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "types.h"
# include "builtins.h"
# include "../libft/libft.h"
# include "utils.h"
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
# include <termios.h>
# include <sys/ioctl.h>
# include <string.h>
# include "../src/utils/tokens/tokens.h"
# include "../src/utils/command/command.h"

typedef struct s_minishell
{
	t_env	*envs;
}	t_minishell;

extern int	g_signal;

void	redirs(t_cmd *cmd);
void	init_signal_ign(void);
void	close_redirs(t_cmd *cmds);
void	print_tokens(t_token *token);
void	print_cmd(t_cmd *cmd);
int		exec_cmd(t_cmd *cmds, t_env **envs);
char	*resolve_path(char *file, t_env *envs, int key);
int		pipeline(t_cmd *cmds, t_env **envs);
void	close_pipes(int pipes[2][2], size_t i, t_cmd *cmd);
int		child_processpipe(size_t index, int pipes[2][2],
			t_cmd *cmds, t_env **envs);
void	setup_signals(void (**old_int)(int), void (**old_quit)(int));
int		fork_child(t_exec *exec, size_t i, int pipes[2][2]);
int		execute_pipeline(t_exec *exec, int pipes[2][2]);
void	error_heredoc(char *delimiter);
int		wait_processes(t_cmd *cmds);
void	heredoc_signal(int signal);
void	init_signal(void);
void	handler_signal(int sig);
void	cmd_signal(int sig);

void	free_and_exit(t_cmd *cmds, t_env *envs, int exit_code, char *msg);
bool	is_valid_number(const char *str);
bool	is_overflowing(const char *str);
void	handle_exit_error(t_cmd *cmd, t_env *envs, char *arg);
int		check_exit_args(t_cmd *cmd, t_env **envs);

char	*get_path(t_cmd *cmd, t_env **envs);
void	tilted_path(t_env **envs, char **path);
void	error(char *msg, char *more);
void	error_write(char *cmd);
int		main(int argc, char **argv, char **envp);
void	increment_shlvl(t_env *new_env);
int		relaunch_minishell(t_env *env);
void	set_stat(t_env **env, int stat);
void	increment_shlvl(t_env *new_env);
char	*append_str(char *str, const char *append);
char	*get_next_value(t_env *env, char *str);
char	*hd_replace_env(t_env *env, char *str);
int		get_stat(t_env *envs);

#endif