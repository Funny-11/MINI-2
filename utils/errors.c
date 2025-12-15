/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:10:01 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/14 14:48:48 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(const char *msg)
{
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	exit(1);
}

void	error_msg(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		if (arg)
		{
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(arg, STDERR_FILENO);
		}
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
}

void	handle_execve_error(char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		error_msg(cmd, NULL, "Permission denied\n");
		exit(126);
	}
	else
	{
		command_not_found(cmd);
		exit(127);
	}
}

int	check_numeric_arg(const char *arg)
{
	long num;

	if (!ft_isdigit(arg))
	{
		error_msg(cmd, arg, "numeric argument required\n");
		return (0);
	}
	num = ft_atol(arg);
	if (num < INT_MIN || num > INT_MAX)
	{
		error_msg(cmd, arg, "numeric argument required\n");
		return (0);
	}
	return (1);
}
