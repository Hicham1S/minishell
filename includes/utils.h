#ifndef UTILS_H
# define UTILS_H

# include "types.h"
# include <stddef.h>
# include <stdbool.h>

# define BUILTIN_NOT_FOUND -1
# define HEREDOC_FILE ".heredoc"

// utils/error.c
void	error(char *msg, char *more);

//utils/exec/redires2.c
void	redir_heredoc2(t_cmd *cmd);

#endif