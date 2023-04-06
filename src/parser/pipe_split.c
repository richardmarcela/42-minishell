/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:05:37 by riolivei          #+#    #+#             */
/*   Updated: 2023/04/06 18:18:56 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_commands	*lstnew_split(t_tokens *token)
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

static t_commands	*lstlast_split(t_commands *lst)
{
	if (!lst)
        return (NULL);
   	while (lst->next)
        lst = lst->next;
    return (lst);
}

static void	lstadd_back_split(t_commands **lst, t_commands *new)
{
	t_commands	*tail;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tail = lstlast_split(*lst);
	tail->next = new;
}

void	pipe_split(char *str, char **envp)
{
	int			i;
	char		**pipe_splitted;
	t_commands	*head;
	t_commands	*current_node;
	t_env	*env;
	
	i = 0;
	pipe_splitted = ft_split(str, '|');
	if (!pipe_splitted[0])
		return ;
	head = lstnew_split(token_list(pipe_splitted[i], env));
	current_node = head;
	while (pipe_splitted[++i])
	{
		current_node = lstnew_split(token_list(pipe_splitted[i], env));
		lstadd_back_split(&head, current_node);
		current_node = current_node->next;
	}
	env = init_env(env, head);
	parser(head);
}
