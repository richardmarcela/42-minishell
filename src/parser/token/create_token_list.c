/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:54:22 by mrichard          #+#    #+#             */
/*   Updated: 2023/04/21 18:19:22 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//NOTA: -n e a unica flag valida para o echo neste projeto
//se for introduzido "echo -a", "-a" deve ser considerado uma OPTION
//pelo lexer, mas posteriormente processado como um ARG
//ERRO cat \"-a"
#include "minishell.h"

static TokenType	token_type(char *str)
{
	if (is_option(str))
		return (OPTION);
	if (is_pipe(str))
		return (PIPE);
	if (is_redirect(str))
		return(which_red(str));
	return (ARG);
}

t_tokens	*lstnew_token(char *str, TokenType type)
{
	t_tokens	*node;

	node = malloc(sizeof(t_tokens));
	if (node == NULL)
		return (NULL);
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

t_tokens    *token_list(char *line)
{
	int     	i;
	char    	**splitted;
	TokenType	type;
	t_tokens	*head;
	t_tokens	*current_node;
	
	i = 0;
	splitted = ft_split(line, ' ');
	head = define_head(splitted, &i);
	current_node = head;
	while (splitted[++i])
	{
		type = token_type(splitted[i]);
		current_node = lstnew_token(splitted[i], type);
		lstadd_back_token(&head, current_node);
		current_node = current_node->next;
	}
	return (head);
}
