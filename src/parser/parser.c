/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:26:06 by riolivei          #+#    #+#             */
/*   Updated: 2023/05/27 18:21:14 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**fill_ops(void)
{
	char	**ops;

	ops = (char **)malloc(sizeof(char *) * 7);
	ops[0] = "<>";
	ops[1] = "<<";
	ops[2] = ">>";
	ops[3] = "<";
	ops[4] = ">";
	ops[5] = "|";
	ops[6] = NULL;
	return (ops);
}

static void	adding_new_token(t_tokens *token, int pos, char *op)
{
	char		*original_str;
	char		*op_str;
	char		*new_str;
	t_tokens	*op_token;
	t_tokens	*new_token;

	new_str = NULL;
	new_token = NULL;
	if (ft_strlen(token->str) > ft_strlen(op))
	{
		original_str = token->str;
		op_str = ft_substr(original_str, pos, ft_strlen(op));
		if (search_content(original_str, op, 0))
		{
			token->str = ft_substr(original_str, 0, pos);
			token->type = token_type(token->str);
			op_token = lstnew_token(op_str, token_type(op_str));
			op_token->next = token->next;
			token->next = op_token;
		}
		if (search_content(original_str, op, 1))
		{
			new_str = ft_substr(original_str, pos + ft_strlen(op),
					ft_strlen(original_str) - ft_strlen(op_str)
					- ft_strlen(token->str));
			new_token = lstnew_token(new_str, token_type(new_str));
			token->str = op_str;
			token->next = new_token;
		}
	}
}

static void	check_tokens(t_tokens *token)
{
	int			i;
	int			pos;
	char		**ops;
	t_tokens	*head;

	head = token;
	ops = fill_ops();
	while (token)
	{
		i = -1;
		while (ops[++i])
		{
			pos = search_ops_in_str(token->str, ops[i], ft_strlen(token->str));
			if (pos > -1 && !has_open_quotes(token->str, pos))
			{
				adding_new_token(token, pos, ops[i]);
				token = token->next;
				break ;
			}
		}
		token = token->next;
	}
}

int	process_tokens(t_commands *command)
{
	t_tokens	*head;

	head = command->token;
	if (!search_ops_in_str(head->str, ".", ft_strlen(head->str))
		|| !search_ops_in_str(head->str, "/", ft_strlen(head->str)))
		return (run_cmd(head->str, head, command->env));
	while (command->token)
	{
		if (has_open_quotes(command->token->str,
				ft_strlen(command->token->str)))
			return (ERROR);
		command->token = command->token->next;
	}
	command->token = head;
	if (!check_builtins(command) && !check_bins(command->token, command->env))
		return (0);
	return (1);
}

void	parser(t_commands *commands)
{
	int	res;

	while (commands)
	{
		check_tokens(commands->token);
		res = process_tokens(commands);
		if (res != 1)
		{
			if (res == ERROR)
			{
				g_exit_status = 2;
				printf("EXIT STATUS UNCLOSED QUOTES: %lld\n", g_exit_status);
				printf("%s\n", EPROMPT);
			}
			else
				printf("%s\n", CNF);
		}
		commands = commands->next;
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//open_pipe(commands);
}
