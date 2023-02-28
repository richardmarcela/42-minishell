/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:32:24 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/28 21:44:53 by riolivei         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "minishell: "
# define EPROMPT "> "
# define CNF "command not found"
# define UNKNOWN "No such file or directory"
# define PD "Permission denied"

//OUTPUT.C
void	output(char *command);

//PROCESSING.C
int		processing(char **line);

//UTILS.C
char	*current_directory(void);
int		count(char *command, int n);

//DIRECTORY.C
void	change_dir(char *dir);
void	content_dir(char *content);

//SPLIT.C
char	**ft_split(char const *s, char c);

//PRINT.C
void	print(char *command);

//QUOTES.C
void	no_quotes(char *command);
void	double_quotes(char *command);
void	single_quotes(char *command);

#endif