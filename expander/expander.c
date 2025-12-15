/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:07:51 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/15 07:04:22 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_var_char(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	if (ft_isdigit(c))
		return (1);
	return (0);
}

static char	*extract_var_name(const char *str, int *i)
{
	int		start;
	int		len;
	char	*var_name;

	start = *i;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	while (str[*i] && is_valid_var_char(str[*i]))
		(*i)++;
	len = *i - start;
	if (len == 0)
		return (NULL);
	var_name = ft_substr(str, start, len);
	if (!var_name)
		error_exit(ERR_MALLOC);
	return (var_name);
}

static char	*get_var_value(t_env *env, const char *var_name, int exit_status)
{
	char	*value;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(exit_status));
	value = get_env_value(env, var_name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static char	*expand_var_in_string(char *str, int *i, t_env *env, int exit_status)
{
	char	*before;
	char	*var_name;
	char	*var_value;
	char	*after;
	char	*result;

	before = ft_substr(str, 0, *i);
	(*i)++;
	var_name = extract_var_name(str, i);
	if (!var_name)
	{
		result = ft_strjoin(before, "$");
		free(before);
		return (result);
	}
	var_value = get_var_value(env, var_name, exit_status);
	free(var_name);
	after = ft_strdup(str + *i);
	result = ft_strjoin(before, var_value);
	free(before);
	free(var_value);
	result = ft_strjoin(result, after);
	free(after);
	*i = ft_strlen(result) - ft_strlen(str + *i);
	return (result);
}
void	expand_variables(char *str, t_env *env, int exit_status)
{
	char	*result;
	char	*tmp;
	int		i;
	int		in_single_quote;
	int		in_double_quote;

	if (!str)
		return (NULL);

	result = ft_strdup(str);
	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	
	while (result[i])
	{
		if (result[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (result[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (result[i] == '$' && !in_single_quote)
		{
			tmp = expand_var_in_string(result, &i, env, exit_status);
			free(result);
			result = tmp;
			continue ;
		}
		i++;
	}
	free(str);
	return (result);
}

static char	*remove_quotes_after_expand(char *str)
{
	char	*result;
	int		i;
	int		j;
	char	quote;

	if (!str)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && !quote)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	free(str);
	return (result);
}

static char	*expand_arg(char *arg, t_env *env, int exit_status)
{
	char	*expanded;
	char	*cleaned;

	if (!arg)
		return (NULL);
	expanded = expand_variables(arg, env, exit_status);
	if (!expanded)
		return (NULL);
	cleaned = remove_quotes_after_expand(expanded);
	free(expanded);
	return (cleaned);
}

void	expand_cmd_variables(t_cmd *cmds, t_env *env, int exit_status)
{
	t_cmd	*cmd;
	int		i;
	char	*expanded;

	cmd = cmds;
	while (cmd)
	{
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			expanded = expand_arg(cmd->args[i], env, exit_status);
			if (!expanded)
			{
				free(cmd->args[i]);
				cmd->args[i] = expanded;
			}
			i++;
		}
		t_redir *redir = cmd->redirs;
		while (redir)
		{
			expanded = expand_arg(redir->filename, env, exit_status);
			if (!expanded)
			{
				free(redir->filename);
				redir->filename = expanded;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}