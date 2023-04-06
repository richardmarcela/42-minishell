/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:13:13 by mrichard          #+#    #+#             */
/*   Updated: 2023/04/06 16:44:00 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*lstnew_env(char *str)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->str = str;
    node->was_declared = 0;
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

static void	lstadd_back_env(t_env **lst, t_env *new)
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

t_env   *init_env(char **envp)
{
    int     i;
    t_env   *head;
    t_env   *current_node;
    
    i = 0;
    head = lstnew_env(envp[i]);
    current_node = head;
    while(envp[++i])
    {
        current_node = lstnew_env(envp[i]);
        lstadd_back_env(&head, current_node);
        current_node = current_node->next;
    }
    return (head);
}
