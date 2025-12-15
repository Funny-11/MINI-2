/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:09:22 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/15 04:01:49 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_var(t_env **env, const char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!*env)
		return ;
	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int builtin_unset(char **args, t_shell *shell)
{
	int	i;
	int	exit_status;

	if (!args[1])
		return (0);
	
	exit_status = 0;
	i = 1;
	while (args[i])
	{
		if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
		{
			error_msg("unset", args[i], "not a valid identifier\n");
			exit_status = 1;
		}
		else
		remove_env_var(&shell->env, args[i]);
		i++;
	}
	return (exit_status);
}