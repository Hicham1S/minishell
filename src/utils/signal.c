/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:18:14 by hsarraj           #+#    #+#             */
/*   Updated: 2025/01/28 16:18:14 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	heredoc_signal(int signal, t_cmd *cmd)
{
	g_exit_status = signal;
	if (cmd)
		cmd->has_heredoc = true;
	set_env(&t_minishell.envs, "?", ft_itoa(128 + g_exit_status));
}

void	cmd_signal(int signal)
{
	g_exit_status = signal;
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	if (signal == SIGQUIT)
	{
		ft_putendl_fd("Quit", STDERR_FILENO);
	}
}