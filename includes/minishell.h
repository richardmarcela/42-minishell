/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:32:24 by riolivei          #+#    #+#             */
/*   Updated: 2023/03/25 22:27:58 by riolivei         ###   ########.fr       */
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
	NONE
}	TokenType;

typedef struct s_tokens
{
	char 					*str;
	TokenType 				token;
	struct s_tokens 	*next;
}				t_tokens;

typedef struct s_commands
{
	t_token *token;
	int		stdin;
	int		stdout;
	struct s_commands	*next;
}				t_commands;

//PARSER/TOKEN/CREATE_TOKEN_LIST.C
void    		token_list(char *line);
void			lstadd_back(t_tokens **lst, t_tokens *new);
TokenType		token_type(char *str);
t_tokens	*lstnew(char *str, TokenType type);
t_tokens	*lstlast(t_tokens *lst);

//PARSER/TOKEN/DEF_TOKEN_TYPE.C
int				is_option(char *str);
int 			is_pipe(char *str);
int				is_redirect(char *str);

//UTILS/UTILS.C
int 			isquote(int c);
void    		ft_free(t_tokens *command);

//PARSER/PIPE_SPLIT.C
int	pipe_split(char *str);

#endif