/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:08:46 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/15 06:30:10 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_var(t_env **env, char *key, char *value)
{
	t_env	*current;
	t_env	*new;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		error_exit(ERR_MALLOC);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (!*env)
		*env = new;
	else
	{
		current = *env;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

static char *get_current_dir(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		error_msg("minishell", NULL, "Failed to get current directory");
	return (cwd);
}
int	builtin_cd(char **args, t_shell *shell)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	oldpwd = get_current_dir();
	if (!oldpwd)
		return (1);
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		path = get_env_value(shell->env, "HOME");
		if (!path)
		{
			error_msg("minishell", "cd", "HOME not set");
			free(oldpwd);
			return (1);
		}
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		path = get_env_value(shell->env, "OLDPWD");
		if (!path)
		{
			error_msg("minishell", "cd", "OLDPWD not set");
			free(oldpwd);
			return (1);
		}
		ft_putendl_fd(path, STDOUT_FILENO);
	}
	else
		path = args[1];
	if (chdir(path) == -1)
	{
		error_msg("minishell", path, strerror(errno));
		free(oldpwd);
		return (1);
	}
	update_env_var(&shell->env, "OLDPWD", oldpwd);
	free(oldpwd);
	newpwd = get_current_dir();
	if (newpwd)
	{
		update_env_var(&shell->env, "PWD", newpwd);
		free(newpwd);
	}
		return (0);
}