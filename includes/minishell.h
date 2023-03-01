/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:32:24 by riolivei          #+#    #+#             */
/*   Updated: 2023/03/01 20:41:30 by mrichard         ###   ########.fr       */
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

# define PROMPT "minishell: "
# define EPROMPT "> "
# define CNF "command not found"
# define UNKNOWN "No such file or directory"
# define PD "Permission denied"
# define ASPAS 34
# define PLICAS 39

//GLOBAL
extern char    **global_env;

//OUTPUT.C
void	output(char *command);

//PROCESSING.C
int		processing(char **line);

//UTILS.C
char	*current_directory(void);
int		count(char *command, int n);
void	exit_and_free(void);
void	ft_free(char **ptr);
int	    ft_start_with(char *s1, char *s2);

//DIRECTORY.C
void	change_dir(char *dir);

//SPLIT.C
char	**ft_split(char const *s, char c);

//PRINT.C
void	print(char *command);

//QUOTES.C
void	no_quotes(char *command);
void	double_quotes(char *command);
void	single_quotes(char *command);

//ENV.C
//int	    print_env();

//SETENV.C
char	*get_env_var(char *var);
//int	    setenv();

//UNSETENV.C
//int     unsetenv();

//EXECUTABLES
void    init_env(char **envp);
int     run_cmd(char *path, char **args);
int	    check_bins(char **line);

//SIGNAL_HANDLER.C
void    proc_signal_handler(int sig);

#endif