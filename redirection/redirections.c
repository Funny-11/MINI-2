/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:20:21 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/15 18:28:47 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int open_redir_in(char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		error_msg("minishell", file, strerror(errno));
		return (-1);
	}
	return (fd);
}

int open_redir_out(char *file)
{
	int fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		error_msg("minishell", file, strerror(errno));
		return (-1);
	}
	return (fd);
}

int open_redir_append(char *file)
{
	int fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		error_msg("minishell", file, strerror(errno));
		return (-1);
	}
	return (fd);
}

static int handle_heredoc(const char *delimiter)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror_msg("pipe", NULL);
		return (-1);
	}
	setup_heredoc_signals();
	while (11)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, pipe_fd[1]);
		free(line);
	}
	close(pipe_fd[1]);
	setup_signals();
	return (pipe_fd[0]);
}

static int	handle_single_redir(t_redir *redir)
{
	int fd;

	if (redir->type == TOKEN_REDIR_IN)
		fd = open_redir_in(redir->filename);
	else if (redir->type == TOKEN_REDIR_OUT)
		fd = open_redir_out(redir->filename);
	else if (redir->type == TOKEN_REDIR_APPEND)
		fd = open_redir_append(redir->filename);
	else if (redir->type == TOKEN_HEREDOC)
		fd = handle_heredoc(redir->filename);
	else
		return (-1);
	if (fd == -1)
		return (-1);
	if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HEREDOC)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror_msg("dup2", NULL);
			close(fd);
			return (-1);
		}
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror_msg("dup2", NULL);
			close(fd);
			return (-1);
		}
	}
	close(fd);
	return (0);
}

int handle_redirections(t_redir *redirs)
{
	t_redir	*current;

	current = redirs;
	while (current)
	{
		if (handle_single_redir(current) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}
