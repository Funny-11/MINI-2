/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:09:11 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/15 03:58:35 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Funzione di supporto per verificare se un nome di variabile è valido
//deve iniziare con lettere o underscore, può contenere lettere, numeri o underscore
static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_exported_list(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(current->key, STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(current->value, STDOUT_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
		current = current->next;
	}
}

static int	add_or_update_var(t_env **env, char *arg)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	t_env	*current;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		key = ft_substr(arg, 0, equal_sign - arg);
		value = ft_strdup(equal_sign + 1);
	}
	else
	{
		key = ft_strdup(arg);
		value = ft_strdup("");
	}
	if (!is_valid_identifier(key))
	{
		error_msg("export", arg, "not a valid identifier\n");
		free(key);
		free(value);
		return (1);
	}
	value = ft_strdup(equal_pos + 1);
	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = value;
			free(key);
			return (0);
		}
		current = current->next;
	}
	t_env *new_var = malloc(sizeof(t_env));
	if (!new_var)
	{
		free(key);
		free(value);
		return (1);
	}
	new_var->key = key;
	new_var->value = value;
	new_var->next = NULL;
	if (!*env)
		*env = new_var;
	else
	{
		current = *env;
		while (current->next)
			current = current->next;
		current->next = new_var;
	}
	return (0);
}

int builtin_export(char **args, t_shell *shell)
{
	int	i;
	int	exit_status;

	if (!args[1])
	{
		print_exported_list(shell->env);
		return (0);
	}
	i = 1;
	exit_status = 0;
	while (args[i])
	{
		if (add_or_update_var(&shell->env, args[i]) != 0)
			exit_status = 1;
		i++;
	}
	return (exit_status);
}