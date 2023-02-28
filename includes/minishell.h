/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:32:24 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/28 05:22:05 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <dirent.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "minishell: "
# define CNF "command not found"
# define UNKNOWN "No such file or directory"
# define PD "Permission denied"

//OUTPUT.C
void	output(char **line);

//PROCESSING.C
int		processing(char **line);

//UTILS.C
int		ft_strcmp(char *s1, char *s2);
char	*current_directory(void);
int		ft_strlen(char *str);

//DIRECTORY.C
void	change_dir(char *dir);
void	content_dir(char *content);

//SPLIT.C
char	**ft_split(char const *s, char c);

//PRINT.C
void	print(char **str);

#endif