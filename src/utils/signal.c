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

#include "../../includes/minishell.h"

void	main_signal(int signal, t_cmd *cmd, t_env *envs)
{
	g_exit_status = signal;
	if (signal == SIGINT)
	{
		if (!cmd->has_heredoc)
			write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		set_env(&envs, "?", ft_itoa(128 + g_exit_status));
	}
}

void	heredoc_signal(int signal)
{
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	close(STDIN_FILENO);
	g_exit_status = signal;

}

void	handler_signal(int sig)
{
	if (sig == SIGQUIT)
		return ;
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_signal(void)
{
	signal(SIGINT, &handler_signal);
	signal(SIGQUIT, SIG_IGN);
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
