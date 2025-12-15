/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:37:03 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/15 06:27:46 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(cmd->args));
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (builtin_cd(cmd->args, shell));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (builtin_export(cmd->args, shell));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (builtin_unset(cmd->args, shell));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (builtin_env(shell->env));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (builtin_exit(cmd->args, shell));
	return (1);
}