/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:32:24 by riolivei          #+#    #+#             */
/*   Updated: 2023/03/30 22:52:40 by mrichard         ###   ########.fr       */
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

typedef enum {
	COMMAND, //ls, wc, echo (builtin, executables)
	OPTION, //-a, -l... (flags)
	PIPE, // |
	ARG, //entre "" ou '', o que vem dps de um command... echo a, echo -n a. a = arg em ambos os casos
	RED_IN, // <
	RED_OUT, // >
	APPEND_IN, // <<
	APPEND_OUT, // >> 
	IN_OUT, // <>
	NONE,
	ERRO
}	TokenType;

typedef struct s_tokens
{
	char 					*str;
	TokenType 				type;
	struct s_tokens 		*next;
}				t_tokens;

typedef struct s_commands
{
	t_tokens 				*token;
	int						stdin;
	int						stdout;
	struct s_commands		*next;
}				t_commands;

typedef struct s_env
{
	char 					*str;
	int						was_declared;
	struct s_env			*next;
}				t_env;

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
void			pipe_split(char *str, char **envp);

//PARSER/PARSER.C
void    		parser(t_commands *commands, char **envp);
TokenType   	which_red(char *str);

//PARSER/ENV_LIST.C
t_env    		*init_env(char **envp);

//PARSER/TOKEN/TOKEN_UTILS.C
int 			token_check_bins(char *str);
int 			token_check_builtins(char *str);

#endif