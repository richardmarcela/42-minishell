/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:16:01 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/08 16:44:05 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*lstnew_env(char *envp, int flag)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->was_added = flag;
	node->str = envp;
	node->next = NULL;
	return (node);
}

static t_env	*lstlast_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*tail;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tail = lstlast_env(*lst);
	tail->next = new;
}

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*head;
	t_env	*current;

	i = -1;
	head = lstnew_env(envp[++i], 0);
	current = head;
	while (envp[++i])
	{
		current = lstnew_env(envp[i], 0);
		lstadd_back_env(&head, current);
	}
	return (head);
}
