/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:32:24 by riolivei          #+#    #+#             */
/*   Updated: 2023/05/20 18:19:11 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"

extern int	g_exit_status;

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

//PARSER/TOKEN/CREATE_TOKEN_LIST.C
t_tokens    	*token_list(char *line);
t_tokens		*lstnew_token(char *str, TokenType type);
void			lstadd_back_token(t_tokens **lst, t_tokens *new);

//PARSER/TOKEN/TOKEN_UTILS.C
TokenType   	which_red(char *str);
t_tokens 		*define_head(char **splitted, int *i);
char			**fill_args(t_tokens *token);

//BUILTINS/CHECK_BUILTINS.C
int				check_builtins(t_commands *command);

//BINS/CHECK_BINS.C
int				check_bins(t_tokens *token, t_env *env);
int				run_cmd(char *bin_path, t_tokens *token, t_env *env);
int				env_len(t_env *env);

//BINS/SIGNAL_HANDLER.C
void			handle_global_signals(void);
void			handle_cmd_signals(void);

//BUILTINS/ECHO/ECHO.C
int				print(t_tokens *token);
int				count(char *command, int n);

//BUILTINS/ECHO/ECHO2.C
void			process_argument(char *str);
void			change_flag(bool *flag);
char			*get_variable(char *str, int *pos);

//BUILTINS/DIRECTORY/DIRECTORY.C
int				change_dir(char *dir, t_env *env);

//BUILTINS/EXPORT/EXPORT.C
int				export(t_commands *command);

//BUILTINS/EXPORT/EXPORT_UTILS.C
char			*process_env_variable(char *str, t_env *env);

//BUILTINS/ENV/ENV.C
int				env(t_env *env);
char			*env_value(char *str, t_env *env);

//BUILTINS/ENV/UNSET.C
int 			unset_env(t_commands *command);

//PARSER/ENV/CREATE_ENV_LIST.C
char			**fill_env_matrix(t_env *env);
t_env			*init_env(char **envp);
t_env			*lstnew_env(char *envp);
void			lstadd_back_env(t_env **lst, t_env *new);

//SRC/PIPE/PIPE.C
void            open_pipe(t_commands *commands);

#endif
