/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dawwad <dawwad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:53:03 by dawwad            #+#    #+#             */
/*   Updated: 2025/03/10 14:53:03 by dawwad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"
# include <stddef.h>
# include <stdbool.h>

# define BUILTIN_NOT_FOUND -1
# define HEREDOC_FILE ".heredoc"
# define HEREDOC_PATH "/tmp/ .minishell_heredoc"

// utils/error.c
void	error(char *msg, char *more);
void	error_invalid_cd(char *path, t_env **envs);
void	print_cd_getcwd_error(void);

//utils/exec/redires2.c
void	redir_heredoc2(t_cmd *cmd);
bool	redir_heredoc(t_env *envs, char *delimiter, t_cmd *cmd);
void	handle_heredoc_line(t_env *envs, char *line, int write_fd);

//args
size_t	get_args_size(t_token *token, int limit[2]);

#endif