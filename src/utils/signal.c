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

void	heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	handler_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signal(void)
{
	signal(SIGINT, handler_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	cmd_signal(int sig)
{
	g_signal = sig;
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
}
