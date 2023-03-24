/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:32:24 by riolivei          #+#    #+#             */
/*   Updated: 2023/03/24 21:04:30 by mrichard         ###   ########.fr       */
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

typedef enum {
	COMMAND,
	OPTION,
	PIPE,
	ARG
}	TokenType;

typedef struct s_command_line
{
	char 					*str;
	TokenType 				token;
	struct s_command_line 	*next;
}				t_command_line;

void    *init(t_command_line *command, char *line);
void    ft_free(t_command_line *command);
void    lexer(char *line);
t_command_line	*lstnew(char *str);
void	lstadd_back(t_command_line **lst, t_command_line *new);
t_command_line	*lstlast(t_command_line *lst);

#endif