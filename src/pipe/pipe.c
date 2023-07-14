/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:14:37 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/13 20:42:19 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	left_pipe(int curr_pipe[2])
{
	close(curr_pipe[0]);
	dup2(curr_pipe[1], STDOUT_FILENO);
	close(curr_pipe[1]);
}

static void	right_pipe(int prev_pipe[2])
{
	close(prev_pipe[1]);
	dup2(prev_pipe[0], STDIN_FILENO);
	close(prev_pipe[0]);
}

static void	error_message(int error, char *mes)
{
	printf("%s\n", mes);
	exit(error);
}

static void	exec_pipe(int prev_pipe[2], int curr_pipe[2],
	int size, t_commands *commands)
{
	pid_t		child;

	child = fork();
	if (child == -1)
		error_message(g_exit_status, PF);
	else if (child == 0)
	{
		if (commands->index > 0)
			right_pipe(prev_pipe);
		if (commands->index < size - 1)
			left_pipe(curr_pipe);
		close_all(prev_pipe, curr_pipe);
		parser(commands);
		exit(g_exit_status);
	}
	else
	{
		assign_pipes(prev_pipe, curr_pipe, commands->index, size);
		waitpid(child, (int *)&g_exit_status, 0);
		g_exit_status = WEXITSTATUS(g_exit_status);
	}
}

void	open_pipe(t_commands *commands)
{
	int		prev_pipe[2];
	int		curr_pipe[2];
	int		size;
	int		i;

	prev_pipe[0] = 0;
	prev_pipe[1] = 0;
	i = -1;
	size = lstsize_commands(commands);
	if (size == 1)
		return (parser(commands));
	while (++i < size)
	{
		commands->index = i;
		if (commands->index < size - 1 && (pipe(curr_pipe) == -1))
			error_message(g_exit_status, PF);
		exec_pipe(prev_pipe, curr_pipe, size, commands);
		if (commands->next)
			commands = commands->next;
	}
}
