/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:05:37 by riolivei          #+#    #+#             */
/*   Updated: 2023/04/21 22:40:27 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lstsize_commands(t_commands *commands)
{
	int	count;

	count = 0;
	while (commands)
	{
		count++;
		commands = commands->next;
	}
	return (count);
}

static t_commands	*lstnew_commands(t_tokens *token)
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

static t_commands	*lstlast_commands(t_commands *lst)
{
	if (!lst)
        return (NULL);
   	while (lst->next)
        lst = lst->next;
    return (lst);
}

static void	lstadd_back_commands(t_commands **lst, t_commands *new)
{
	t_commands	*tail;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tail = lstlast_commands(*lst);
	tail->next = new;
}

void	pipe_commands(char *str, char **envp)
{
	int			i;
	char		**pipe_splitted;
	t_commands	*head;
	t_commands	*current_node;
	t_env	*env;
	
	i = 0;
	env = init_env(envp);
	pipe_splitted = ft_split(str, '|');
	//a candonga abaixo executada serve para tratar empty commands (ex: so espacos)
	if (!pipe_splitted[0] || !ft_strtrim(pipe_splitted[0], " ")
		|| !ft_strtrim(ft_strtrim(pipe_splitted[0], " "), " "))
		return	;
	if (has_empty_pipe(pipe_splitted))
	{
		printf("%s\n", EPARSE);
		return ;
	}
	head = lstnew_commands(token_list(pipe_splitted[i]));
	current_node = head;
	while (pipe_splitted[++i])
	{
		current_node = lstnew_commands(token_list(pipe_splitted[i]));
		lstadd_back_commands(&head, current_node);
		current_node = current_node->next;
	}
	parser(head, env);
}
