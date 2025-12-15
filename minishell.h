/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 03:29:03 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/15 07:26:11 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

/* ======== LIBRERIE ==== */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include "libft.h"

/* ======== COSTANTI ==== */
#define PROMPT "minishell$ "
#define MAX_CMD_LENGTH 1024
#define BUFF_SIZE 4096
#define MAX_ARGS 100

/* ======== COLORI OUTPUT ==== */
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define RESET "\033[0m"

/* ======== MSG ERROR ==== */
# define ERR_MALLOC "minishell: Memory allocation failed\n"
# define ERR_SYNTAX "minishell: Syntax error near unexpected token\n"
#define ERR_QUOTES "minishell: Quotes are not closed\n"

/* ======== DEFINIZIONI TIPI TOKEN ======== */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_IN_QUOTE,
	TOKEN_END
} t_token_type;

/* ======== STRUTTURA TOKEN ==== */
typedef struct s_token
{
	t_token_type		type;
	char			*value;
	struct s_token	*next;
} t_token;

/* ======== STRUTTURA REDIRECTION ==== */
typedef struct s_redir
{
	t_token_type			type; // < o > o >> o <<
	char				*filename; // nome del file o delimitatore
	struct s_redirection	*next;
} t_redir;

/* ======== STRUTTURA COMANDO ==== */
//Rappresenta un singolo comando con i suoi argomenti e redirezioni
typedef struct s_cmd
{
	char			**args; // ["echo", "hello", NULL]
	t_redir			*redirs; // lista di redirezioni
	struct s_command	*next; // per le pipe
} t_cmd;

/* ======== VARIABILE D'AMBIENTE ==== */
typedef struct s_env
{
	char				*key; // nome della variabile: ESEMPIO "PATH"
	char				*value; // valore della variabile: ESEMPIO "/usr/bin:/bin"
	struct s_env	*next; // puntatore alla prossima variabile
} t_env;

/* ======== STRUTTURA SHELL ==== */
//Rappresenta tutte le informazioni globali della shell
typedef struct s_shell
{
	t_token	*tokens; // lista di token (output del lexer)
	t_cmd	*cmd_list; // lista di comandi (output del parser)
	t_env	*env; // array di stringhe che sono le variabili d'ambiente
	int		last_exit_status; // codice uscita dell'ultimo comando eseguito
	int		stdin_backup; // backup di stdin per ripristinarlo dopo le redirezioni
	int		stdout_backup; // backup di stdout per ripristinarlo dopo le redirezioni
} t_shell;

/* ======== VARIABILE GLOBALE SEGNALI ======== */
//Deve contenere SOLO il numero del segnale ricevuto
extern int	g_exit_status;

/* =============== PROTOTIPI FUNZIONI ==================== */

/* ======== INIZIALIZZAZIONE SHELL ==== */
t_shell	*init_data(char **envp);
t_env	*init_env(char **envp);
void	minishell_loop(t_shell *shell);

/* ======== LEXER/TOKENIZZAZIONE ==== */
t_token			*lexer(const char *line);
t_token			*create_token(t_token_type type, char *value);
void			token_add_back(t_token **tokens, t_token *new_token);
int				token_count(t_token *tokens);
void			print_tokens(t_token *tokens);
//static int		skip_space(char *line, int i);
//static int		is_operator(char c);
//static int		find_end_word(char *line, int start);
//static char		*remove_quotes(char *str);
//static t_token	*handle_word(char *line, int *i);
//static t_token	*handle_operator(char *line, int *i);



/* ======== PARSER / ANALISI SINTASSI ==== */
t_cmd	*parser(t_token *tokens);
int		check_syntax(t_token *tokens);

/* ======== EXPANDER (Espansione $VAR) ==== */
void		expand_cmdx_variables(t_cmd *cmds, t_env *env, int exit_status);
char		*get_env_value(t_env *envp, const char *key);
int			count_env(char **envp);
char		**copy_env(char **envp);
//static int	is_valid_var_char(char c);
//static char	*extract_var_name(const char *str, int *i);
//static char *get_var_value(t_env *env, const char *var_name, int exit_status);
//static char	*expand_var_in_string(char *str, int *i, t_env *env, int exit_status);
void		expand_variables(char *str, t_env *env, int exit_status);
void		expand_cmd_variables(t_cmd *cmds, t_env *env, int exit_status);
//static char	*remove_quotes_after_expand(char *str);
//static char	*expand_arg(char *arg, t_env *env, int exit_status);

/* ======== EXECUTOR (Esecuzione) ==== */
int			executor(t_cmd *cmds, t_shell *shell);
void		exec_simple_cmd(t_cmd *cmd, t_shell *shell);
void		exec_pipeline(t_cmd *cmds, t_shell *shell);
//static int	count_cmds(t_cmd *cmds);
//static char	**env_to_arr(t_env *env);
//static char	*find_command(char *cmd, t_env *env);
//static void	execute_external_cmd(t_cmd *cmd, t_shell *shell);


/* ======== BUILTINS ==== */
int			is_builtin(const char *cmd);
int			exec_builtin(t_cmd *cmd, t_shell *shell);
int			builtin_echo(char **args);
int			builtin_cd(char **args, t_shell *shell);
int			builtin_pwd(void);
int			builtin_export(char **args, t_shell *shell);
int			builtin_unset(char **args, t_shell *shell);
int			builtin_env(t_env *env);
int			builtin_exit(char **args, t_shell *shell);
//static int	is_valid_identifier(const char *str);
//static int	count_args(char **args);
//static int	is_n_flag(char *arg);
//static int	add_or_update_var(t_env **env, char *arg);
//static void	remove_env_var(t_env **env, const char *key);
//static void	print_exported_list(t_env *env);
//static void	update_env_var(t_env **env, char *key, char *value);
//static char	*get_current_dir(void);


/* ======== REDIRECTION ======== */
int				handle_redirections(t_redir *redirs);
int				open_redir_in(const char *filename);
int				open_redir_out(const char *filename);
int				open_redir_append(const char *filename);
int				handle_heredoc(const char *delimiter);
//static t_redir	*create_redir(t_token_type type, char *filename);
//static void		redir_add_back(t_redir **redirs, t_redir *new_redir);
//static t_redir	*parse_redirections(t_token **current);
//static int		handle_single_redir(t_redir *redir);
//static int		is_redirection(t_token_type type);


/* ======== FREE & CLEAN ======= */
void	free_tokens(t_token *tokens);
void	free_cmds(t_cmd *cmds);
void	free_env(t_env *env);
void	free_envp(char **envp);
void	free_shell(t_shell *shell);
void	free_split(char **split);
void	free_redirs(t_redir *redirs);

/* ======== ERRORS ======= */
void	error_exit(const char *msg);
void	error_msg(char *cmd, char *arg, char *msg);
void	handle_execve_error(char *cmd);
int		check_numeric_arg(const char *arg);

/* ======== SIGNALS ======= */
void	setup_signals(void);
void	setup_child_signals(void);
void	setup_heredoc_signals(void);
void	handler_sigint(int sig);
void	handler_sigquit(int sig);

/* ======== UTILS ======= */
//static int		find_equal_sign(char *str);
//static t_env		*create_env_node(char *env_str);
//static void		env_add_back(t_env **env, t_env *new_node);
//static int		count_tokens_args(t_token *tokens);
//static char		**parse_args(t_token **current);
//static t_cmd	*parse_single_command(t_token **current);

#endif