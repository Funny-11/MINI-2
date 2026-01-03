#include "minishell.h"

void	update_exit_status_from_last_signal(t_shell *shell)
{
	if (g_last_signal == SIGINT)
		shell->exit_status = 130;
	else if (g_last_signal == SIGQUIT)
		shell->exit_status = 131;
	g_last_signal = INT_MIN;
}
