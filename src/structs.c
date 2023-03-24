/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:54:22 by mrichard          #+#    #+#             */
/*   Updated: 2023/03/24 22:16:36 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    lexer(char *line)
{
	t_command_line	*head;
	t_command_line	*current_node;
	char    **splitted;
	int     i;

	i = 0;
	splitted = ft_split(line, ' ');
	head = lstnew(splitted[i]); //criamos uma head
	current_node = head; //dizemos q a head e o node atual
	while (splitted[++i]) //adicionamos novos nodes
	{
		current_node = lstnew(splitted[i]);
		lstadd_back(&head, current_node);
		current_node = current_node->next;
	}
	/* este ciclo e so para correr a lista e ver q funcionou 
	current_node = head;
	while(current_node)
	{
		printf("%s\n", current_node->str);
		current_node = current_node->next;
	} */
}

t_command_line	*lstnew(char *str)
{
	t_command_line	*node;

	node = malloc(sizeof(t_command_line));
	if (node == NULL)
		return (NULL);
	node->str = str;
	node->token = 0;
	node->next = NULL;
	return (node);
}

void	lstadd_back(t_command_line **lst, t_command_line *new)
{
	t_command_line	*tail;

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

t_command_line	*lstlast(t_command_line *lst)
{
	if (!lst)
        return (NULL);
   	while (lst->next)
        lst = lst->next;
    return (lst);
}