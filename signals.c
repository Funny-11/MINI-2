#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;

	g_last_signal = sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_replace_line("", 0);
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
