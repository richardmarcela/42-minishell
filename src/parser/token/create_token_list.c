/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:54:22 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/27 15:59:07 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_TokenType	token_type(char *str, int flag, int was_quoted)
{
	if (is_option(str))
		return (OPTION);
	if (is_pipe(str))
		return (PIPE);
	if (is_redirect(str, was_quoted))
		return (which_red(str));
	if (flag)
		return (COMMAND);
	return (ARG);
}

t_tokens	*lstnew_token(char *str, t_TokenType type)
{
	t_tokens	*node;

	node = malloc(sizeof(t_tokens));
	if (node == NULL)
		return (NULL);
	node->was_quoted = 0;
	node->skip = 0;
	node->str = str;
	node->type = type;
	node->next = NULL;
	return (node);
}

static t_tokens	*lstlast_token(t_tokens *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lstadd_back_token(t_tokens **lst, t_tokens *new)
{
	t_tokens	*tail;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tail = lstlast_token(*lst);
	tail->next = new;
}

t_tokens	*token_list(char *line)
{
	int			i;
	char		*trimmed_line;
	char		**splitted;
	t_tokens	*head;
	t_tokens	*current_node;

	i = 0;
	trimmed_line = ft_strtrim(line, " ");
	splitted = ft_split(trimmed_line, ' ');
	head = lstnew_token(splitted[i], token_type(splitted[i], 1, 0));
	current_node = head;
	while (splitted[++i])
	{
		current_node = lstnew_token(splitted[i], token_type(splitted[i], 0, 0));
		lstadd_back_token(&head, current_node);
	}
	free(splitted);
	free(trimmed_line);
	free(line);
	return (head);
}
