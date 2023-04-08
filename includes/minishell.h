/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:32:24 by riolivei          #+#    #+#             */
/*   Updated: 2023/04/08 22:03:48 by riolivei         ###   ########.fr       */
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

# define PROMPT "minishell 🐚> "
# define EPROMPT "> "
# define CNF "command not found"
# define UNKNOWN "No such file or directory"
# define PD "Permission denied"
# define ASPAS 34
# define PLICAS 39
# define ERROR -1

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
	int						was_declared;
	struct s_env			*next;
}				t_env;

typedef struct s_commands
{
	t_tokens 				*token;
	t_env					*env;
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
void    		ft_free(t_tokens *command);

//PARSER/PIPE_SPLIT.C
void			pipe_commands(char *str, char **envp);

//PARSER/PARSER.C
void    		parser(t_commands *commands, t_env	*env);

//PARSER/ENV_LIST.C
t_env    		*init_env(char **envp);

//PARSER/TOKEN/CREATE_TOKEN_LIST.C
t_tokens	*lstnew_token(char *str, TokenType type);
void	lstadd_back_token(t_tokens **lst, t_tokens *new);

//PARSER/TOKEN/TOKEN_UTILS.C
TokenType   	which_red(char *str);
t_tokens 		*define_head(char **splitted, int *i);

//BUILTINS/CHECK_BUILTINS.C
int	check_builtins(t_tokens *token, t_env *env);

//BINS/CHECK_BINS.C
int	check_bins(char **line);

//BUILTINS/ECHO/ECHO.C
int	print(t_tokens *token);
int	has_unclosed_quotes(char *str);

//BUILTINS/ECHO/ECHO2.C
void	process_argument(char *str);
void	single_quotes(char *command);
void	double_quotes(char *command);
void	no_quotes(char *command);

#endif