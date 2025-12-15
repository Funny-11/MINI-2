/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:42:32 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/15 06:06:06 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_space(char *line, int i)
{
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

static int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static	t_token	*handle_operator(char *line, int *i)
{
	t_token			*token;
	t_token_type	type;
	char			*value;

	if (line[*i] == '|')
	{
		type = TOKEN_PIPE;
		value = ft_strdup("|");
		(*i)++;
	}
	else if (line[*i] == '<')
	{
		if (line[*i + 1] == '<')
		{
			type = TOKEN_HEREDOC;
			value = ft_strdup("<<");
			*i += 2;
		}
		else
		{
			type = TOKEN_REDIR_IN;
			value = ft_strdup("<");
			(*i)++;
		}
	}
	else
	{
		if (line[*i + 1] == '>')
		{
			type = TOKEN_REDIR_OUT_APPEND;;
			value = ft_strdup(">>");
			*i += 2;
		}
		else
		{
			type = TOKEN_REDIR_OUT;
			value = ft_strdup(">");
			(*i)++;
		}
	}
	token = create_token(type, value);
	return (token);
}

static int	find_end_word(char *line, int start)
{
	int	i;
	char	quote;

	i = start;
	quote = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"') && !quote)
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
		else if (!quote)
		{
			if (line[i] == ' ' || line[i] == '\t' || is_operator(line[i]))
				break ;
		}
		i++;
	}
	return (i);
}

static char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	char	quote;

	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		error_exit(ERR_MALLOC);
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
	return (result);
}

static t_token	*handle_word(char *line, int *i)
{
	t_token	*token;
	int		start;
	int		end;
	char	*word;
	char	*cleaned;

	start = *i;
	end = find_end_word(line, start);
	word = ft_substr(line, start, end - start);
	if (!word)
		error_exit(ERR_MALLOC);
	cleaned = remove_quotes(word);
	free(word);d
	if (!cleaned)
		error_exit(ERR_MALLOC);
	token = create_token(TOKEN_WORD, cleaned);
	*i = end;
	return (token);
}

t_token	*lexer(const char *line)
{
	t_token	*tokens;
	t_token	*new_token;
	int		i;

	if (!line || !*line)
		return (NULL);
	tokens = NULL;
	i = 0;
	while (line[i])
	{
		i = skip_space(line, i);
		if (!line[i])
			break ;
		if (is_operator(line[i]))
			new_token = handle_operator(line, &i);
		else
			new_token = handle_word(line, &i);
		if (new_token)
			token_add_back(&tokens, new_token);
		else
		{
			free_tokens(tokens);
			return (NULL);
		}
	}
	new_token = create_token(TOKEN_EOF, NULL);
	token_add_back(&tokens, new_token);
	return (tokens);
}