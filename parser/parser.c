/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:07:34 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/15 07:11:40 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_OUT_APPEND || type == TOKEN_HEREDOC);
}

int	check_syntax(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (current->type == TOKEN_PIPE)
		return (0);
	while (current && current->type != TOKEN_EOF)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (!current->next || current->next->type == TOKEN_EOF || tmp->next->type == TOKEN_PIPE)
				return (0);
		}
		if (is_redirection(current->type))
		{
			if (!current->next || current->next->type != TOKEN_WORD)
				return (0);
		}
		current = current->next;
	}
	return (1);
}

static int	count_tokens_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type == TOKEN_WORD)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

static t_redir	*create_redir(t_token_type type, char *filename)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		error_exit(ERR_MALLOC);
	redir->type = type;
	redir->filename = ft_strdup(filename);
	if (!redir->filename)
	{
		free(redir);
		error_exit(ERR_MALLOC);
	}
	redir->next = NULL;
	return (redir);
}

static void	redir_add_back(t_redir **redirs, t_redir *new_redir)
{
	t_redir	*tmp;

	if (!redirs || !new_redir)
		return ;
	if (!*redirs)
	{
		*redirs = new_redir;
		return ;
	}
	tmp = *redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redir;
}

static t_redir	*parse_redirections(t_token **current)
{
	t_redir	*redirs;
	t_redir	*new_redir;

	redirs = NULL;
	while (*current && is_redirection((*current)->type))
	{
		new_redir = create_redir((*current)->type, (*current)->next->value);
		if (!new_redir)
		{
			while (redirs)
			{
				next_redir = redirs->next;
				free(redirs->filename);
				free(redirs);
				redirs = next_redir;
			}
			return (NULL);
		}
		redir_add_back(&redirs, new_redir);
		*current = (*current)->next->next;
	}
	return (redirs);
}

static char	**parse_args(t_token **current)
{
	char	**args;
	int		count;
	int		i;

	count = count_args(*current);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		error_exit(ERR_MALLOC);
	i = 0;
	while (*current && (*current)->type == TOKEN_WORD)
	{
		args[i] = ft_strdup((*current)->value);
		if (!args[i])
		{
			while (i-- >= 0)
				free(args[i]);
			free(args);
			error_exit(ERR_MALLOC);
		}
		i++;
		*current = (*current)->next;
	}
	args[i] = NULL;
	return (args);
}

static t_cmd	*parse_single_command(t_token **current)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		error_exit(ERR_MALLOC);
	cmd->args = parse_args(current);
	cmd->redirs = parse_redirections(current);
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*new_cmd;
	t_token	*current;

	if (!check_syntax(tokens))
	{
		free_tokens(tokens);
		error_exit(ERR_SYNTAX);
	}
	current = tokens;
	cmd_list = NULL;
	while (current && current->type != TOKEN_EOF)
	{
		new_cmd = parse_single_command(&current);
		if (!new_cmd)
		{
			free_cmds(cmd_list);
			return (NULL);
		}
		if (!cmd_list)
			cmd_list = new_cmd;
		else
			last->next = new_cmd;
		last = new_cmd;
		if (current && current->type == TOKEN_PIPE)
			current = current->next;
	}
	return (cmd_list);
}
