/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 02:01:10 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/01 02:18:07 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static t_env	*create_env_node(char *env_str)
{
	t_env	*new_node;
	int		equal_index;

	equal_index = find_equal_sign(env_str);
	if (equal_index == -1)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);

	new_node->key = ft_substr(env_str, 0, equal_index);
	if (!new_node->key)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = ft_strdup(env_str + equal_index + 1);
	if (!new_node->value)
	{
		free(new_node->key);
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

static void	env_add_back(t_env **env, t_env *new_node)
{
	t_env	*tmp;

	if (!new_node)
		return ;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	t_env	*new_node;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = create_env_node(envp[i]);
		if (!new_node)
		{
			free_env(envp);
			return (NULL);
		}
		env_add_back(&envp, new_node);
		i++;
	}
	return (envp);
}

char	*get_env_value(t_env *env, const char *key)
{
	if (!env || !key)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
