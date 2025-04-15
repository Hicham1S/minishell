/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dawwad <dawwad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:51:11 by dawwad            #+#    #+#             */
/*   Updated: 2025/03/10 14:51:11 by dawwad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

char	**init_args(t_token *token, int limit[2]);
void	cmd_redirs(t_env *envs, t_cmd *cmd, t_token *token, int limit[2]);
void	free_cmd(t_cmd *cmd);
void	process_redir2(t_env *envs, t_cmd *cmd, t_token **current);
void	process_redir(t_cmd *cmd, t_token **current);

#endif