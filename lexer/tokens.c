/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:42:59 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/15 05:24:55 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		error_exit(ERR_MALLOC);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	token_add_back(t_token **tokens, t_token *new_token)
{
	t_token	*tmp;

	if (!tokens || !new_token)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
}

int	token_count(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

void	print_tokens(t_token *tokens)
{
	int	i;
	const char	*type_str;

	i = 0;
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
			type_str = "WORD";
		else if (tokens->type == TOKEN_PIPE)
			type_str = "PIPE";
		else if (tokens->type == TOKEN_REDIR_IN)
			type_str = "REDIR_IN";
		else if (tokens->type == TOKEN_REDIR_OUT)
			type_str = "REDIR_OUT";
		else if (tokens->type == TOKEN_REDIR_OUT_APPEND)
			type_str = "REDIR_OUT_APPEND";
		else if (tokens->type == TOKEN_HEREDOC)
			type_str = "HEREDOC";
		else
			type_str = "END";
		if (tokens->value)
			printf("[%d] %s: \"%s\"\n", i, type_str, tokens->value);
		else
			printf("[%d] %s\n", i, type_str);
		tokens = tokens->next;
		i++;
	}
}
