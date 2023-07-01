/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:32:24 by riolivei          #+#    #+#             */
/*   Updated: 2023/07/01 19:10:39 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"

extern long long	g_exit_status;

//PARSER/TOKEN/DEF_TOKEN_TYPE.C
int				is_option(char *str);
int				is_pipe(char *str);
int				is_redirect(char *str);

//UTILS/UTILS.C
int				isquote(int c);
int				has_empty_pipe(char **splitted);
int				lstsize_tokens(t_tokens *token, int filter);
int				search_ops_in_str(char *s1, char *s2, int n);

//UTILS/UTILS2.C

//PARSER/PIPE_SPLIT.C
void			pipe_commands(char *str, t_env *env);

//PARSER/PARSER.C
int				process_tokens(t_commands *command);
void			parser(t_commands *commands);

//PARSER/PARSER_UTILS.C
int				search_content(char *str, char *op, int flag);
void			handle_content_before(t_tokens *token, int pos,
					char *op_str, char *original_str);
t_tokens		*handle_content_after(char *original_str, int pos,
					char *op, t_tokens *token);

//PARSER/TOKEN/CREATE_TOKEN_LIST.C
t_tokens		*token_list(char *line);
t_tokens		*lstnew_token(char *str, t_TokenType type);
t_TokenType		token_type(char *str);
void			lstadd_back_token(t_tokens **lst, t_tokens *new);

//PARSER/TOKEN/TOKEN_UTILS.C
t_TokenType		which_red(char *str);
char			**fill_args(t_tokens *token);

//BUILTINS/CHECK_BUILTINS.C
int				check_builtins(t_commands *command);

//BINS/CHECK_BINS.C
int				check_bins(t_tokens *token, t_env *env);
int				run_cmd(char *bin_path, t_tokens *token, t_env *env);
int				env_len(t_env *env);

//BINS/CHECK_BINS_UTILS.C
char			**get_path(t_env *env);
char			*get_bin_path(char *path, char *str);
int				check_awk(t_tokens *token, char *bin_path);

//BINS/SIGNAL_HANDLER.C
void			handle_global_signals(void);
void			handle_cmd_signals(void);

//BUILTINS/ECHO/ECHO.C
int				print(t_tokens *token, t_env *env);
int				count(char *command, int n);

//BUILTINS/ECHO/ECHO2.C
void			process_argument(char *str, t_env *env);
void			change_flag(bool *flag);
char			*get_variable(char *str, int *pos);

//BUILTINS/DIRECTORY/DIRECTORY.C
int				change_dir(t_tokens *token, t_env *env);

//BUILTINS/EXPORT/EXPORT.C
bool			*attr_values_quotes(void);
int				export(t_commands *command);

//BUILTINS/EXPORT/EXPORT_UTILS.C
char			*process_env_variable(char *str, t_env *env);
char			*env_search_variable(char *command, int *pos, t_env *env);
char			*env_quote_handler(char *str, int *pos,
					bool **quotes, t_env *env);

//BUILTINS/EXPORT/EXPORT_UTILS2.C
char			*attr_value_result(char *result, char *input, int *i, t_env *env);

//BUILTINS/ENV/ENV.C
int				env(t_env *env);
char			*env_value(char *str, t_env *env);

//BUILTINS/ENV/UNSET.C
int				unset_env(t_commands *command);

//PARSER/ENV/CREATE_ENV_LIST.C
char			**fill_env_matrix(t_env *env);
t_env			*init_env(char **envp);
t_env			*lstnew_env(char *envp);
void			lstadd_back_env(t_env **lst, t_env *new);

//SRC/PIPE/PIPE.C
void			open_pipe(t_commands *commands);

//SRC/PIPE/PIPE_UTILS.C
void			assign_pipes(int prev_pipe[2], int curr_pipe[2],
					int i, int size);
void			close_all(int prev_pipe[2], int curr_pipe[2]);
void			free_structs(t_commands *commands, int flag);

//SRC/REDIRECTIONS/REDIRECTIONS.C
void			handle_redir(t_tokens *token);

//SRC/BUILTINS/EXIT.C
int				exit_terminal(t_commands *command);

int				lstsize_commands(t_commands *commands);

#endif
