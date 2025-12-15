/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:09:34 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/15 04:02:51 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		ft_putstr_fd(current->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putendl_fd(current->value, STDOUT_FILENO);
		current = current->next;
	}
	return (0);
}