/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:14:37 by mrichard          #+#    #+#             */
/*   Updated: 2023/05/27 18:10:04 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	left_pipe(t_commands *commands, int pipedes[2])
{
	close(STDOUT_FILENO);
	dup(pipedes[1]);
	close(pipedes[0]);
	close(pipedes[1]);
	(void)commands;
	//function to exec commands, should be parser or process_tokens?
	//process_tokens(commands);
}

static void	right_pipe(t_commands *commands, int pipedes[2])
{
	close(STDIN_FILENO);
	dup(pipedes[0]);
	close(pipedes[0]);
	close(pipedes[1]);
	(void)commands;
	//function to exec commands, should be parser or process_tokens?
	//process_tokens(commands);
}

void	open_pipe(t_commands *commands)
{
	pid_t	child;
	int		pipedes[2];
	int		temp;

	if (pipe(pipedes) == -1)
	{
		printf("pipe() failed\n");
		exit(g_exit_status);
	}
	child = fork();
	if (child == -1)
	{
		printf("fork() failed\n");
		exit(g_exit_status);
	}
	if (child == 0)
		left_pipe(commands, pipedes);
	right_pipe(commands->next, pipedes);
	close(pipedes[0]);
	close(pipedes[1]);
	waitpid(child, &temp, 0);
	g_exit_status = temp >> 8;
}

/* 127, i.e command not found, comes from waitpid as 32512. 32512 >> 8 = 127 */