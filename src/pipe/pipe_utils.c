/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:15:51 by mrichard          #+#    #+#             */
/*   Updated: 2023/06/23 18:13:08 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <errno.h>

void	assign_pipes(int prev_pipe[2], int curr_pipe[2], int i, int size)
{
	if (i > 0)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	if (i < size - 1)
	{
		prev_pipe[0] = curr_pipe[0];
		prev_pipe[1] = curr_pipe[1];
	}
}

void	close_all(int prev_pipe[2], int curr_pipe[2])
{
	close(prev_pipe[0]);
	close(prev_pipe[1]);
	close(curr_pipe[0]);
	close(curr_pipe[1]);
}

void	free_tokens(t_tokens *token)
{
	int			size;
	int			i;
	t_tokens	*node;
	
	i = -1;
	size = lstsize_tokens(token, 0);
	while (++i < size)
	{
		node = token;
		token = token->next;
		free(node->str);
		free(node);
	}
}

void	free_structs(t_commands *commands)
{
	int			size;
	int			i;
	t_commands	*node;
	
	i = -1;
	size = lstsize_commands(commands);
	while (++i < size)
	{
		node = commands;
		free_tokens(commands->token);
		commands = commands->next;
		free(node);
	}
}
