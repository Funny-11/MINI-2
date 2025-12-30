/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:37:03 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/30 23:42:36 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", SIZE_MAX) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", SIZE_MAX) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", SIZE_MAX) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", SIZE_MAX) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", SIZE_MAX) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", SIZE_MAX) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", SIZE_MAX) == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->args[0], "echo", SIZE_MAX) == 0)
		return (builtin_echo(cmd->args));
	else if (ft_strncmp(cmd->args[0], "cd", SIZE_MAX) == 0)
		return (builtin_cd(cmd->args, shell));
	else if (ft_strncmp(cmd->args[0], "pwd", SIZE_MAX) == 0)
		return (builtin_pwd());
	else if (ft_strncmp(cmd->args[0], "export", SIZE_MAX) == 0)
		return (builtin_export(cmd->args, shell));
	else if (ft_strncmp(cmd->args[0], "unset", SIZE_MAX) == 0)
		return (builtin_unset(cmd->args, shell));
	else if (ft_strncmp(cmd->args[0], "env", SIZE_MAX) == 0)
		return (builtin_env(shell->env));
	else if (ft_strncmp(cmd->args[0], "exit", SIZE_MAX) == 0)
		return (builtin_exit(cmd->args, shell));
	return (1);
}