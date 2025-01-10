/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:53:29 by hsarraj           #+#    #+#             */
/*   Updated: 2025/01/10 10:53:29 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "types.h"

typedef struct s_builtin
{
	char	*name;
	int		(*func)(t_cmd *cmd, t_env **envs);
}	t_builtin;

int	builtin_cd(t_cmd *cmd, t_env **envs);
int	builtin_echo(t_cmd *cmd, t_env **envs);
int	builtin_env(t_cmd *cmd, t_env **envs);
int	builtin_exit(t_cmd *cmd, t_env **envs);
int	builtin_export(t_cmd *cmd, t_env **envs);
int	builtin_pwd(t_cmd *cmd, t_env **envs);
int	builtin_unset(t_cmd *cmd, t_env **envs);

#endif