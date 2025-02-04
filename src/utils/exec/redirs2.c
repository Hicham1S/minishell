/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:54:34 by hsarraj           #+#    #+#             */
/*   Updated: 2025/01/28 17:54:34 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	redir_heredoc2(t_cmd *cmd)
{
	rl_getc_function = rl_getc;
	close(cmd->infile);
	unlink(HEREDOC_FILE);
}
