/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:32:24 by riolivei          #+#    #+#             */
/*   Updated: 2023/05/06 19:38:48 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "shell pequeno 🐚> "
# define EPARSE "parse error near '|'"
# define EPROMPT "unclosed quotes"
# define CNF "shell pequeno: command not found"
# define UNKNOWN "no such file or directory"
# define PD "permission denied"
# define ASPAS 34
# define PLICAS 39
# define ERROR -1
# define PERROR -2

typedef enum TokenType
{
	SETTING, //setting a variable (fds=a)
	COMMAND, //ls, wc, echo (builtin, executables)
	OPTION, //-a, -l... (flags)
	PIPE, // |
	ARG, //entre "" ou '', o que vem dps de um command... echo a, echo -n a. a = arg em ambos os casos
	RED_IN, // <
	RED_OUT, // >
	APPEND_IN, // <<
	APPEND_OUT, // >> 
	IN_OUT, // <>
	ERRO
}	TokenType;

typedef struct s_tokens
{
	char 					*str;
	TokenType 				type;
	struct s_tokens 		*next;
}				t_tokens;

typedef struct s_env
{
	char 					*str;
	/* int						was_declared; */
	struct s_env			*next;
}				t_env;

typedef struct s_commands
{
	t_env					*env;
	t_tokens 				*token;
	int						stdin;
	int						stdout;
	struct s_commands		*next;
}				t_commands;

//PARSER/TOKEN/CREATE_TOKEN_LIST.C
t_tokens    	*token_list(char *line);

//PARSER/TOKEN/DEF_TOKEN_TYPE.C
int				is_option(char *str);
int 			is_pipe(char *str);
int				is_redirect(char *str);

//UTILS/UTILS.C
int 			isquote(int c);
int				has_empty_pipe(char **splitted);
void    		ft_free(t_tokens *command);
int 			lstsize_tokens(t_tokens *token);
int				search_ops_in_str(char *s1, char *s2, int n);

//PARSER/PIPE_SPLIT.C
void			pipe_commands(char *str, t_env *env);

//PARSER/PARSER.C
int				process_tokens(t_commands *command);
void    		parser(t_commands *commands);

//PARSER/ENV_LIST.C
t_env			*init_env(char **envp);

//PARSER/TOKEN/CREATE_TOKEN_LIST.C
t_tokens		*lstnew_token(char *str, TokenType type);
void			lstadd_back_token(t_tokens **lst, t_tokens *new);

//PARSER/TOKEN/TOKEN_UTILS.C
TokenType   	which_red(char *str);
t_tokens 		*define_head(char **splitted, int *i);
int				count_token(t_tokens *token);
char			**fill_args(t_tokens *token);

//BUILTINS/CHECK_BUILTINS.C
int				check_builtins(t_commands *command);

//BINS/CHECK_BINS.C
int				check_bins(t_tokens *token, t_env *env);
void    		proc_signal_handler(int sig);
int				run_cmd(char *bin_path, t_tokens *token, t_env *env);
int				env_len(t_env *env);

//BUILTINS/ECHO/ECHO.C
int				print(t_tokens *token);
int				has_unclosed_quotes(t_tokens *token);
int				count(char *command, int n);

//BUILTINS/ECHO/ECHO2.C
void			process_argument(char *str);

//BUILTINS/DIRECTORY/DIRECTORY.C
int				change_dir(char *dir);

//BUILTINS/EXPORT/EXPORT.C
int				export(t_commands *command);

//BUILTINS/ENV/ENV.C
int				env(t_env *env);

//BUILTINS/ENV/ENV.C
char			**fill_env_matrix(t_env *env);
t_env	*lstnew_env(char *envp);
void	lstadd_back_env(t_env **lst, t_env *new);

void	handle_global_signals(void);
void	handle_cmd_signals(void);
#endif
