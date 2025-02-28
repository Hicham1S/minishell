#ifndef UTILS_H
# define UTILS_H

# include "types.h"
# include <stddef.h>
# include <stdbool.h>

# define BUILTIN_NOT_FOUND -1
# define HEREDOC_FILE ".heredoc"

// utils/error.c
void	error(char *msg, char *more);
void	error_invalid_cd(char *path, t_env **envs);

//utils/exec/redires2.c
void	redir_heredoc2(t_cmd *cmd);
bool redir_heredoc(char *delimiter, t_cmd *cmd);


//args
size_t	get_args_size(t_token *token, int limit[2]);

#endif