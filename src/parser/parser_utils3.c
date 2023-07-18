/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:54:06 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/18 18:32:34 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir(t_commands *command)
{
	t_TokenType	type;
	t_tokens	*head;

	printf("ENTROU CHECK REDIR\n");
	head = command->token;
	while (command->token)
	{
		if (!command->token->was_quoted)
		{
			type = command->token->type;
			if (type >= 5 && type <= 8 && !command->token->next)
			{
				command->token = head;
				return (0);
			}
		}
		command->token = command->token->next;
	}
	command->token = head;
	printf("SAIU CHECK REDIR\n");
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
