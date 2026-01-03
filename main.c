/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <marvin>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:43:44 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/30 22:55:32 by gifanell         ###   ########.fr       */
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
}

t_shell	*init_data(t_shell *shell, char **envp)
{
	shell->tokens = NULL;
	shell->cmd_list = NULL;
	shell->env = init_env(envp);
	shell->exit_status = 0;
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
	return (shell);
}

void	minishell_loop(t_shell *shell)
{
	while (11)
	{
		setup_signals();
		shell->prompt = readline(GREEN "minishell$ " RESET);
		update_exit_status_from_last_signal(shell);
		if (!shell->prompt)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (shell->prompt[0] == '\0')
		{
			free(shell->prompt);
			shell->prompt = NULL;
			continue ;
		}
		add_history(shell->prompt);
		shell->prompt = expand_variables(shell->prompt, shell->env, shell->exit_status);
		shell->tokens = lexer(shell->prompt);
		free(shell->prompt);
		shell->prompt = NULL;
		if (!shell->tokens)
		{
			continue ;
		}
		if (!check_syntax(shell->tokens))
		{
			ft_putstr_fd(ERR_SYNTAX, STDERR_FILENO);
			shell->exit_status = 2;
			free_tokens(shell->tokens);
			shell->tokens = NULL;
			continue ;
		}
		shell->cmd_list = parser(shell, shell->tokens);
		if (!shell->cmd_list)
		{
			free_tokens(shell->tokens);
			shell->tokens = NULL;
			continue ;
		}
		// expand_variables((char *)shell->cmd_list, shell->env, shell->exit_status);
		shell->exit_status = executor(shell->cmd_list, shell);
		free_tokens(shell->tokens);
		free_cmds(shell->cmd_list);
		shell->tokens = NULL;
		shell->cmd_list = NULL;
		dup2(shell->stdin_backup, STDIN_FILENO); // ripristina stdin/stdout perché potrebbero essere stati modificati/redirezionati
		dup2(shell->stdout_backup, STDOUT_FILENO);
	}
}

int	g_last_signal = INT_MIN;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	g_last_signal = INT_MIN;
	shell = (t_shell){0};
	init_data(&shell, envp);
	minishell_loop(&shell);
	free_shell(&shell);
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
