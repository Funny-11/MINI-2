/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:08:07 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/14 19:43:11 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**env_to_arr(t_env *env)
{
	char	**envp;
	t_env	tmp;
	int		count;
	int		i;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		error_exit(ERR_MALLOC);
	tmp = env;
	i = 0;
	while (tmp)
	{
		envp[i] = ft_strdup(tmp->var);
		if (!envp[i])
		{
			while (i-- >= 0)
				free(envp[i]);
			free(envp);
			error_exit(ERR_MALLOC);
		}
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

static char	*find_command(char *cmd, t_env *env)
{
	char	**path_env;
	char	**paths;
	char	*full_path;
	char	*tmp;
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		error_exit(ERR_MALLOC);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

static void	execute_external_cmd(t_cmd *cmd, t_shell *shell)
{
	char	**envp;
	char	*cmd_path;

	cmd_path = find_command(cmd->args[0], shell->env);
	if (!cmd_path)
	{
		handle_execve_error(cmd->args[0]);
	}
	envp = env_to_arr(shell->env);
	if (!envp)
		error_exit(ERR_MALLOC);
	execve(cmd_path, cmd->args, envp);
	free(cmd_path);
	free_split(envp);
	handle_execve_error(cmd->args[0]);
}

void	exec_simple_cmd(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (is_builtin(cmd->args[0]))
	{
		if (cmd->redirs)
		{
			if (handle_redirections(cmd->redirs) == -1)
			{
				shell->exit_status = 1;
				return ;
			}
		}
		shell->exit_status = exec_builtin(cmd, shell);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		setup_child_signals();
		if (cmd->redirs)
		{
			if (handle_redirections(cmd->redirs) == -1)
				exit(1);
		}
		execute_external_cmd(cmd, shell);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}

static int	count_cmds(t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

void exec_pipeline(t_cmd *cmds, t_shell *shell)
{
	int		num_cmds;
	int		i;
	pid_t	*pids;
	int		**pipes;
	t_cmd	*current;

	num_cmds = count_cmds(cmds);
	pipes = malloc(sizeof(int *) * (num_cmds - 1));
	if (!pipes)
		error_exit(ERR_MALLOC);
	i = 0;
	while (i < num_cmds - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			perror_msg("pipe", NULL);
			while (--i >= 0)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				free(pipes[i]);
			}
			free(pipes);
			shell->exit_status = 1;
			return ;
		}
		i++;
	}
	pids = malloc(sizeof(pid_t) * num_cmds);
	if (!pids)
	{
		i = 0;
		while (i < num_cmds - 1)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			free(pipes[i]);
			i++;
		}
		free(pipes);
		error_exit(ERR_MALLOC);
	}
	i = 0;
	current = cmds;
	while (current)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror_msg("fork", NULL);
			return ;
		}
		if (pids[i] == 0)
		{
			setup_child_signals();
			if (i > 0)
			{
				dup2(pipes[i - 1][0], STDIN_FILENO);
			}
			if (i < num_cmds - 1)
			{
				dup2(pipes[i][1], STDOUT_FILENO);
			}
			int j;
			while (j < num_cmds - 1)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
			if (current->redirs)
			{
				if (handle_redirections(current->redirs) == -1)
					exit(1);
			}
			if (is_builtin(current->args[0]))
			{
				(exec_builtin(current, shell));
				exit(shell->exit_status);
			}
			else
			{
				execute_external_cmd(current, shell);
			}
		}
		i++;
		current = current->next;
	}
	i = 0;
	while (i < num_cmds - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	i = 0;
	while (i < num_cmds)
	{
		int status;
		waitpid(pids[i], &status, 0);
		if (i == num_cmds - 1)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	free(pipes);
	free(pids);
}

int	executor(t_cmd *cmds, t_shell *shell)
{
	if (!cmds)
		return (0);
	if (!cmds->next)
	{
		exec_simple_cmd(cmds, shell);
	}
	else
		exec_pipeline(cmds, shell);
	return (shell->exit_status);
}
