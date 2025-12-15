/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 00:16:37 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/15 07:30:22 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	
	g_exit_status = 130;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
}

void	handler_sigquit(int sig)
{
	(void)sig;
	//Ignora SIGQUIT
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handler_sigquit);
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

/*
void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	//Ignora SIGQUIT durante heredoc
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
	
	//SIGINT durante heredoc: comportamento speciale
	//Interrompe l'input e ritorna al prompt
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}*/