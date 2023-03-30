/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:54:22 by mrichard          #+#    #+#             */
/*   Updated: 2023/03/25 23:14:00 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//NOTA: -n e a unica flag valida para o echo neste projeto
//se for introduzido "echo -a", "-a" deve ser considerado uma OPTION
//pelo lexer, mas posteriormente processado como um ARG
//ERRO cat \"-a"
#include "minishell.h"

void    token_list(char *line)
{
	int     	i;
	char    	**splitted;
	TokenType	type;
	t_tokens	*head;
	t_tokens	*current_node;

	i = 0;
	splitted = ft_split(line, ' ');
	type = token_type(splitted[i]);
	if (type == NONE)
	{
		printf("%s%s\n", PROMPT, UNKNOWN);
		return ;
	}
	head = lstnew(splitted[i], type);
	current_node = head;
	while (splitted[++i])
	{
		type = token_type(splitted[i]);
		if (type == NONE)
		{
			printf("%s%s\n", PROMPT, UNKNOWN);
			break ;
		}	
		current_node = lstnew(splitted[i], type);
		lstadd_back(&head, current_node);
		current_node = current_node->next;
	}
	/* current_node = head;
	while(current_node)
	{
		printf("%s\n", current_node->str);
		printf("%u\n", current_node->token);
		current_node = current_node->next;
	} */
}

TokenType	token_type(char *str)
{
	if (is_option(str))
		return (OPTION);
	if (is_pipe(str))
		return (PIPE);
	if (is_redirect(str))
		//return (); QUAL DOS REDIRECTS?
/* 	if (is_arg())
	if (is_command())*/
	return (NONE);
}

t_tokens	*lstnew_token(char *str, TokenType type)
{
	t_tokens	*node;

	node = malloc(sizeof(t_tokens));
	if (node == NULL)
		return (NULL);
	node->str = str;
	node->token = type;
	node->next = NULL;
	return (node);
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
	tail = lstlast(*lst);
	tail->next = new;
}

t_tokens	*lstlast_token(t_tokens *lst)
{
	if (!lst)
        return (NULL);
   	while (lst->next)
        lst = lst->next;
    return (lst);
}