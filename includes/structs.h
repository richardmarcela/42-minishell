/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:19:19 by mrichard          #+#    #+#             */
/*   Updated: 2023/05/21 21:04:00 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H 

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
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
# define CNF "command not found"
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

typedef struct s_pipe
{
    int fds[2];
    struct s_pipe *next;
} t_pipe;

#endif