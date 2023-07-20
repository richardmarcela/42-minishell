/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:54:06 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/20 21:29:17 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_tokens *token)
{
	t_TokenType	type;
	t_TokenType	type_next;

	type = token->type;
	if (type == 9)
		return (0);
	if (type >= 5 && type <= 8)
	{
		if (!token->next)
			return (0);
		type_next = token->next->type;
		if (type_next >= 5 && type_next <= 8)
			return (0);
	}
	return (1);
}

int	check_redir(t_commands *command)
{
	t_tokens	*head;

	head = command->token;
	while (command->token)
	{
		if (!command->token->was_quoted)
		{
			if (!check_syntax(command->token))
			{
				command->token = head;
				return (0);
			}
		}
		if (command->token->next)
			command->token = command->token->next;
		else
			break ;
	}
	command->token = head;
	return (1);
}

int	has_in_out(t_commands *command, t_tokens *head)
{
	int	len;

	len = ft_strlen(command->token->str);
	if (!has_open_quotes(command->token->str, len))
	{
		if (ft_strnstr(command->token->str, "<>", len))
		{
			command->token = head;
			printf("%s\n", SE);
			return (1);
		}
	}
	return (0);
}

void	search_for_redirs(t_commands *command)
{
	int		i;
	char	**ops;

	i = -1;
	ops = fill_ops();
	while (ops[++i])
	{
		if (ft_strnstr(command->token->str, ops[i], ft_strlen(command->token->str)))
		{
			command->token->was_quoted = 1;
			break ;
		}
	}
	free(ops);
	return ;
}
