/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:43:44 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/15 07:18:48 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->cmd_list)
		free_cmds(shell->cmd_list);
	if (shell->env)
		free_env(shell->env);
	if (shell->stdin_backup != -1)
		close(shell->stdin_backup);
	if (shell->stdout_backup != -1)
		close(shell->stdout_backup);
	free(shell);
}

t_shell	*init_data(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		error_exit(ERR_MALLOC);
	shell->tokens = NULL;
	shell->cmd_list = NULL;
	shell->env = init_env(envp);
	shell->last_exit_status = 0;
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
	return (shell);
}

void	minishell_loop(t_shell *shell)
{
	char	*line;

	while (11)
	{
		line = readline(GREEN "minishell$ " RESET);
		if (!line)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		shell->tokens = lexer(line);
		free(line);
		if (!shell->tokens)
		{
			continue ;
		}
		if (!check_syntax(shell->tokens))
		{
			ft_putstr_fd(ERR_SYNTAX, STDERR_FILENO);
			shell->last_exit_status = 2;
			free_tokens(shell->tokens);
			shell->tokens = NULL;
			continue ;
		}
		shell->cmd_list = parser(shell->tokens);
		if (!shell->cmd_list)
		{ 
			free_tokens(shell->tokens);
			shell->tokens = NULL;
			continue ;
		}
		expand_variables((char *)shell->cmd_list, shell->env, shell->last_exit_status);
		shell->last_exit_status = executor(shell->cmd_list, shell);
		free_tokens(shell->tokens);
		free_cmds(shell->cmd_list);
		shell->tokens = NULL;
		shell->cmd_list = NULL;
		dup2(shell->stdin_backup, STDIN_FILENO); // ripristina stdin/stdout perché potrebbero essere stati modificati/redirezionati
		dup2(shell->stdout_backup, STDOUT_FILENO);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;

	setup_signals();
	shell = init_data(envp);
	minishell_loop(shell);
	free_shell(shell);
	return (0);
}
/*
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	int	i = 0;

	printf("=== VARIABILI D'AMBIENTE ===\n");
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
*/