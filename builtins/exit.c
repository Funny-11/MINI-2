/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <marvin>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:09:43 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/28 14:55:19 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

int	builtin_exit(char **args, t_shell *shell)
{
	int		exit_status;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (count_args(args) > 2)
	{
		error_msg("exit", NULL, "too many arguments\n");
		return (1);
	}
	if (args[1])
	{
		if (!check_numeric_arg("exit", args[1]))
		{
			error_msg("exit", args[1], "numeric argument required\n");
			exit_status = 255;
		}
		else
			exit_status = ft_atoi(args[1]) % 256;
	}
	else
		exit_status = shell->last_exit_status;
	free_shell(shell);
	exit(exit_status);
}
