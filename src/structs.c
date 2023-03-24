/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:54:22 by mrichard          #+#    #+#             */
/*   Updated: 2023/03/24 21:42:22 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    lexer(char *line)
{
	t_command_line	*temp;
	t_command_line	*head;
	char    **splitted;
	int     i;

	i = -1;
	head = NULL;
	splitted = ft_split(line, ' ');
	while (splitted[++i])
	{
		temp = lstnew(splitted[i]);
		lstadd_back(&head, temp);
		temp = temp->next;
		printf("%s\n", temp->str);
	}
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