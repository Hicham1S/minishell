/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 10:48:09 by hsarraj           #+#    #+#             */
/*   Updated: 2025/01/12 10:48:09 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	heredoc_child_process(t_env *envs, char *delimiter, int write_fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			fprintf(stderr,
				"minishell: warning: here-document at line %d delimited by EOF"
				" (wanted `%s')\n", __LINE__, delimiter);
			exit(0);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			exit(0);
		}
		handle_heredoc_line(envs, line, write_fd);
		free(line);
	}
}

static int	open_heredoc_file(void)
{
	return (open(HEREDOC_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

static int	fork_heredoc(t_env *envs, char *delimiter, int fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		heredoc_child_process(envs, delimiter, fd);
		exit(1);
	}
	close(fd);
	return (pid);
}

static bool	setup_heredoc_signals(pid_t pid, void (*old_int)(int),
					void (*old_quit)(int))
{
	int	status;

	waitpid(pid, &status, 0);
	signal(SIGINT, old_int);
	signal(SIGQUIT, old_quit);
	if ((status % 128) != 0)
	{
		g_signal = status % 128;
		unlink(HEREDOC_PATH);
		return (false);
	}
	else if ((status >> 8) != 0)
	{
		unlink(HEREDOC_PATH);
		return (false);
	}
	return (true);
}

bool	redir_heredoc(t_env *envs, char *delimiter, t_cmd *cmd)
{
	int		fd;
	pid_t	pid;
	void	(*old_int)(int);
	void	(*old_quit)(int);

	fd = open_heredoc_file();
	if (fd < 0)
		return (false);
	old_int = signal(SIGINT, SIG_IGN);
	old_quit = signal(SIGQUIT, SIG_IGN);
	pid = fork_heredoc(envs, delimiter, fd);
	if (pid < 0)
		return (false);
	if (!setup_heredoc_signals(pid, old_int, old_quit))
		return (false);
	fd = open(HEREDOC_PATH, O_RDONLY);
	if (fd < 0)
	{
		unlink(HEREDOC_PATH);
		return (false);
	}
	cmd->infile = fd;
	cmd->has_heredoc = 1;
	return (true);
}
