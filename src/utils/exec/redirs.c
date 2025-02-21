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

// static void	reopen_heredoc(t_cmd *cmd)
// {
//     if (cmd->infile >= 0)
//         close(cmd->infile);
//     cmd->infile = open(HEREDOC_FILE, O_RDONLY);
//     if (cmd->infile < 0)
//         perror("Error reopening heredoc");
// }

// bool	redir_heredoc(char *delimiter, t_cmd *cmd)
// {
// 	char	*line;

// 	cmd->infile = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (cmd->infile < 0)
// 		return (error("heredoc", strerror(errno)), false);
// 	cmd->has_heredoc = true;
// 	while (1)
// 	{
// 		signal(SIGINT, heredoc_signal);
// 		signal(SIGQUIT, SIG_IGN);
// 		line = readline("> ");
// 		if (!line && g_sginal == SIGINT)
// 			break;
// 		else if (!line)
// 			return (reopen_heredoc(cmd), error_heredoc(delimiter), true);
// 		if (ft_strcmp(line, delimiter) == 0)
// 			return (reopen_heredoc(cmd), free(line), true);
// 		ft_putendl_fd(line, cmd->infile);
// 		free(line);
// 	}
// 	redir_heredoc2(cmd);
// 	return (true);
// }
// bool redir_heredoc(char *delimiter, t_cmd *cmd)
// {
//     int     fd;
//     pid_t   pid;
//     int     status;
//     char    *line;
	
//     fd = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd < 0)
//         return (error("heredoc", strerror(errno)), false);
	
//     cmd->has_heredoc = true;
//     g_sginal = 0;
	
//     // // Store original handlers
//     void (*original_sigint)(int) = signal(SIGINT, SIG_IGN);
//     void (*original_sigquit)(int) = signal(SIGQUIT, SIG_IGN);
//     pid = fork();
//     if (pid < 0)
//     {
//         close(fd);
//         signal(SIGINT, original_sigint);
//         signal(SIGQUIT, original_sigquit);
//         return (error("fork", strerror(errno)), false);
//     }
	
//     if (pid == 0)  // Child process
//     {
//         signal(SIGINT, SIG_DFL);
//         signal(SIGQUIT, SIG_IGN);
//         while (1)
//         {
//             line = readline("> ");
//             if (!line)
//             {
//                 close(fd);
//                 exit(0);
//             }
//             if (ft_strcmp(line, delimiter) == 0)
//             {
//                 free(line);
//                 close(fd);
//                 exit(0);
//             }
//             write(fd, line, ft_strlen(line));
//             write(fd, "\n", 1);
//             free(line);
//         }
//     }
	
//     // Parent process waits
//     close(fd);
//     waitpid(pid, &status, 0);
	
//     // Restore original signal handlers
//     signal(SIGINT, original_sigint);
//     signal(SIGQUIT, original_sigquit);
	
	
//     if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
//     {
//         g_sginal = SIGINT;
//         write(STDOUT_FILENO, "\n", 1);
//         rl_on_new_line();
//         rl_replace_line("", 0);
//         unlink(HEREDOC_FILE);
//         return false;
//     }
	
//     fd = open(HEREDOC_FILE, O_RDONLY);
//     if (fd < 0)
//     {
//         error("heredoc", strerror(errno));
//         unlink(HEREDOC_FILE);
//         return false;
//     }
	
//     unlink(HEREDOC_FILE);
	
//     if (fd < 3)
//     {
//         int newfd = dup(fd);
//         close(fd);
//         fd = newfd;
//     }
	
//     cmd->infile = fd;
//     return true;
// }



// static void heredoc_child_process(char *delimiter, int write_fd)
// {
// 	char *line;

// 	// Set up child signal handling
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_IGN);

// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line || g_sginal == SIGINT)
// 		{
// 			if (line)
// 				free(line);
// 			exit(1);
// 		}

// 		if (ft_strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			exit(0);
// 		}

// 		write(write_fd, line, ft_strlen(line));
// 		write(write_fd, "\n", 1);
// 		free(line);
// 	}
// }

// bool redir_heredoc(char *delimiter, t_cmd *cmd)
// {
// 	pid_t   pid;
// 	int     status;
// 	char    *heredoc_file;

// 	// Create temporary file for heredoc
// 	heredoc_file = "/tmp/.minishell_heredoc";
	
// 	// Open file for writing
// 	int fd = open(heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd < 0)
// 		return (false);

// 	// Save original signal handlers
// 	void (*old_int)(int) = signal(SIGINT, SIG_IGN);
// 	void (*old_quit)(int) = signal(SIGQUIT, SIG_IGN);

// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		close(fd);
// 		unlink(heredoc_file);
// 		return (false);
// 	}

// 	if (pid == 0)
// 	{
// 		heredoc_child_process(delimiter, fd);
// 		exit(1);  // Should never reach here
// 	}	
// 	// Parent process
// 	close(fd);
// 	waitpid(pid, &status, 0);

// 	// Restore original signal handlers
// 	signal(SIGINT, old_int);
// 	signal(SIGQUIT, old_quit);

// 	if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0)
// 	{
// 		unlink(heredoc_file);
// 		return (false);
// 	}
	

// 	// Open file for reading
// 	fd = open(heredoc_file, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		unlink(heredoc_file);
// 		return (false);
// 	}

// 	unlink(heredoc_file);  // Delete the temporary file
// 	cmd->infile = fd;
// 	cmd->has_heredoc = 1;
	
// 	return (true);
// }

void	redirs(t_cmd *cmd)
{
	if (cmd->infile >= 0)
		dup2(cmd->infile, STDIN_FILENO);
	if (cmd->outfile >= 0)
		dup2(cmd->outfile, STDOUT_FILENO);
}

void	close_redirs(t_cmd *cmds)
{
	while (cmds)
	{
		if (cmds->infile > 2)
			close(cmds->infile);
		if (cmds->outfile > 2)
			close(cmds->outfile);
		if (cmds->has_heredoc)
			unlink(HEREDOC_FILE);
		cmds = cmds->next;
	}
}
