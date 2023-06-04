/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:14:37 by mrichard          #+#    #+#             */
/*   Updated: 2023/06/04 22:30:35 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	left_pipe(int curr_pipe[2])
{
	close(STDOUT_FILENO);
	close(curr_pipe[0]);
	dup2(curr_pipe[1], STDOUT_FILENO);
	close(curr_pipe[1]);
}

static void	right_pipe(int prev_pipe[2])
{
	close(STDIN_FILENO);
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
	/* int			temp; */
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
		parser(commands);
		exit(g_exit_status);
	}
	else
		assign_pipes(prev_pipe, curr_pipe, commands->index, size);
	/* waitpid(child, &temp, 0);
	g_exit_status = temp >> 8; */
}

void	open_pipe(t_commands *commands)
{
	int		prev_pipe[2];
	int		curr_pipe[2];
	int		size;

	commands->index = -1;
	prev_pipe[0] = 0;
	prev_pipe[1] = 0;
	size = lstsize_commands(commands);
	if (size == 1)
		return (parser(commands));
	while (++commands->index < size)
	{
		if (commands->index < size - 1 && (pipe(curr_pipe) == -1))
			error_message(g_exit_status, PF);
		exec_pipe(prev_pipe, curr_pipe, size, commands);
		if (commands->next)
			commands = commands->next;
	}
	commands->index = -1;
	while (++commands->index < size)
		wait(NULL);
}

/* void	open_pipe(t_commands *commands)
{
	pid_t	child;
	int		pipedes[2];
	int		temp;
	int		size;

	if (pipe(pipedes) == -1) //create a pair of fd 
	{
		printf("pipe() failed\n");
		exit(g_exit_status);
	}
	child = fork();
	if (child == -1)
	{
		printf("%s\n", FF);
		exit(g_exit_status);
	}
	if (child == 0) //means we are in the child process
		left_pipe(commands, piped// Set up output redirection
		if (i < num_commands - 1) {
			dup2(curr_pipe[1], STDOUT_FILENO);
			close(curr_pipe[0]);
			close(curr_pipe[1]);
		}es);
	right_pipe(commands->next, pipedes);
	close(pipedes[0]);
	close(pipedes[1]);
	waitpid(child, &temp, 0); //parent waits for child to finish
	g_exit_status = temp >> 8;
} */

/* 127, i.e command not found, comes from waitpid as 32512. 32512 >> 8 = 127 */

/* void	free_nfd(int **nfd)
{
	int	i;

	i = 0;
	while (nfd[i])
	{
		free(nfd[i]);
		i++;
	}
	free(nfd);
}

int	init_pipe(int **fd, int i, t_commands *current)
{
	fd[i] = malloc(sizeof(int) * 2);
	if (fd[i] == NULL)
		return (50);
	if (pipe(fd[i]) == -1)
		return (40);
	if (i == 0) //first command has the STANDARD INPUT
		current->stdin = 0;
	else
		current->stdin = fd[i - 1][0];
	if (current->next == NULL) //last command 
	{
		close(fd[i][0]);
		close(fd[i][1]);
		current->stdout = 1;
	}
	else
		current->stdout = fd[i][1];
	return (0);
}

int	open_pipe(t_commands *commands)
{
	t_commands	*current;
	int			i;
	int			**fd;
	int			ret;

	i = 0;
	current = commands;
	fd = malloc(sizeof(int *) * (lstsize_commands(commands) + 1));
	if (fd == NULL)
		return (50);
	fd[lstsize_commands(current)] = NULL;
	while (current)
	{
		ret = init_pipe(fd, i, current);
		if (ret != 0)
		{
			free_nfd(fd);
			return (ret);
		}
		current = current->next;
		i++;
	}
	free_nfd(fd);
	return (0);
} */