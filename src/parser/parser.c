/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:26:06 by riolivei          #+#    #+#             */
/*   Updated: 2023/07/14 21:28:42 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	adding_new_token(t_tokens *token, int pos, char *op)
{
	char		*original_str;
	t_tokens	*new_token;

	new_token = NULL;
	if (ft_strlen(token->str) > ft_strlen(op))
	{
		printf("ENTROU IF\n");
		original_str = token->str;
		if (search_content(original_str, op, 0))
		{
			printf("ENTROU CONTENT BEFORE\n");
			handle_content_before(token, pos, op, original_str);
			printf("SAIU CONTENT BEFORE\n");
		}
		if (search_content(original_str, op, 1))
		{
			printf("ENTROU CONTENT AFTER\n");
			new_token = handle_content_after(original_str, pos, op, token);
			if (!search_content(original_str, op, 0))
			{
				token->str = op;
				token->next = new_token;
			}
			else
				token->next->next = new_token;
			printf("SAIU CONTENT AFTER\n");
		}
		free(original_str);
		printf("SAIU IF\n");
	}
}

static void	check_tokens(t_tokens *token)
{
	int			i;
	int			pos;
	char		**ops;

	ops = fill_ops();
	while (token)
	{
		i = -1;
		while (ops[++i])
		{
			pos = search_ops_in_str(token->str, ops[i], ft_strlen(token->str));
			if (pos > -1 && !has_open_quotes(token->str, pos))
			{
				printf("ENTROU ADD TOKEN\n");
				adding_new_token(token, pos, ops[i]);
				printf("SAIU ADD TOKEN\n");
				token = token->next;
				break ;
			}
		}
		token = token->next;
	}
	free(ops);
}

int	process_tokens(t_commands *command)
{
	t_tokens	*head;

	head = command->token;
	if (!search_ops_in_str(head->str, ".", ft_strlen(head->str))
		|| !search_ops_in_str(head->str, "/", ft_strlen(head->str)))
		return (run_cmd(head->str, head, command->env));
	if (!check_bins(command->token, command->env) && !check_builtins(command))
	{
		command->token = head;
		return (0);
	}
	command->token = head;
	return (1);
}

char	*process_argument(t_commands *command)
{
	int		i;
	int		start;
	char	*new_str;
	char	*temp;
	char	*handling;

	i = -1;
	start = 0;
	new_str = NULL;
	while (command->token->str[++i])
	{
		while (command->token->str[i] != '$' && !isquote(command->token->str[i])
			&& command->token->str[i])
			i++;
		new_str = add_chars(new_str, command->token->str, i - start, start);
		if (command->token->str[i] == '$')
		{
			new_str = process_variable(command->token->str, &i,
					new_str, command->env);
			start = i;
			i--;
		}
		else if (isquote(command->token->str[i]))
		{
			temp = new_str;
			handling = quote_handler(command->token->str, &i,
					i + 1, command->env);
			new_str = ft_strjoin(temp, handling);
			free(temp);
			if (handling && ft_strcmp(handling, "$"))
				free(handling);
			start = i + 1;
		}
		else
			break ;
		/* if (!command->token->str[i])
			break ; */
	}
	free(command->token->str);
	return (new_str);
}

void	parser(t_commands *command)
{
	t_tokens	*head;

	head = command->token;
	while (command->token)
	{
		if (has_open_quotes(command->token->str,
				ft_strlen(command->token->str)))
		{
			g_exit_status = 2;
			printf("%s\n", EPROMPT);
			command->token = head;
			return ;
		}
		command->token->str = process_argument(command);
		command->token = command->token->next;
	}
	command->token = head;
	check_tokens(command->token);
	if (!process_tokens(command))
		printf("%s\n", CNF);
}
