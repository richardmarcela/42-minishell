/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:15:51 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/16 21:57:08 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <errno.h>

void	assign_pipes(int prev_pipe[2], int curr_pipe[2], int i, int size)
{
	printf("ENTROU ASSIGN\n");
	printf("- PREV 0: %d\n", prev_pipe[0]);
	printf("- PREV 1: %d\n", prev_pipe[1]);
	printf("- CURR 0: %d\n", curr_pipe[0]);
	printf("- CURR 1: %d\n", curr_pipe[1]);
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
	printf("- PREV 0 AFTER: %d\n", prev_pipe[0]);
	printf("- PREV 1 AFTER: %d\n", prev_pipe[1]);
	printf("- CURR 0 AFTER: %d\n", curr_pipe[0]);
	printf("- CURR 1 AFTER: %d\n", curr_pipe[1]);
	printf("- SAIU\n");
}

void	close_all(int prev_pipe[2], int curr_pipe[2])
{
	printf("ENTROU CLOSE\n");
	printf("- PREV 0: %d\n", prev_pipe[0]);
	printf("- PREV 1: %d\n", prev_pipe[1]);
	printf("- CURR 0: %d\n", curr_pipe[0]);
	printf("- CURR 1: %d\n", curr_pipe[1]);
	close(prev_pipe[0]);
	close(prev_pipe[1]);
	if (curr_pipe[0] != STDIN_FILENO)
		close(curr_pipe[0]);
	close(curr_pipe[1]);
	printf("SAIU\n");
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

void	free_env(t_env *env)
{
	int		i;
	int		size;
	t_env	*node;

	i = -1;
	size = env_len(env);
	while (++i < size)
	{
		node = env;
		env = env->next;
		if (node->was_added)
			free(node->str);
		free(node);
	}
}

void	free_structs(t_commands *commands, int flag)
{
	int			size;
	int			i;
	t_commands	*node;

	i = -1;
	if (flag)
		free_env(commands->env);
	size = lstsize_commands(commands);
	while (++i < size)
	{
		node = commands;
		free_tokens(commands->token);
		commands = commands->next;
		free(node);
	}
}
