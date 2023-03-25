/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:05:37 by riolivei          #+#    #+#             */
/*   Updated: 2023/03/25 22:41:55 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_split(char *str)
{
	int			i;
	char		**pipe_splitted;
	t_commands	*head;
	t_commands	*current_node;
	
	i = 0;
	pipe_splitted = ft_split(line, '|');
	head = lstnew(token_list(pipe_splitted[i]), type);
	current_node = head;
	while (pipe_splitted[++i])

		token_list(pipe_splitted[i]);
}

t_commands	*lstnew(t_tokens *token, TokenType type)
{
	t_commands	*node;

	node = malloc(sizeof(t_commands));
	if (node == NULL)
		return (NULL);
	node->token = token;
	node->stdin = 0;
	node->stdout = 1;
	node->next = NULL;
	return (node);
}

void	lstadd_back(t_commands **lst, t_commands *new)
{
	t_commands	*tail;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tail = lstlast(*lst);
	tail->next = new;
}

t_commands	*lstlast(t_commands *lst)
{
	if (!lst)
        return (NULL);
   	while (lst->next)
        lst = lst->next;
    return (lst);
}