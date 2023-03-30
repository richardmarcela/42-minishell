/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:05:37 by riolivei          #+#    #+#             */
/*   Updated: 2023/03/30 22:49:09 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_commands	*lstnew(t_tokens *token)
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

static void	lstadd_back(t_commands **lst, t_commands *new)
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

static t_commands	*lstlast(t_commands *lst)
{
	if (!lst)
        return (NULL);
   	while (lst->next)
        lst = lst->next;
    return (lst);
}

void	pipe_split(char *str, char **envp)
{
	int			i;
	char		**pipe_splitted;
	t_commands	*head;
	t_commands	*current_node;
	
	i = 0;
	pipe_splitted = ft_split(str, '|');
	if (!pipe_splitted[0])
		return ;
	head = lstnew(token_list(pipe_splitted[i]));
	current_node = head;
	while (pipe_splitted[++i])
	{
		current_node = lstnew(token_list(pipe_splitted[i]));
		lstadd_back(&head, current_node);
		current_node = current_node->next;
	}
	parser(head, envp);
}
