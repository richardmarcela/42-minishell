/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:14:37 by mrichard          #+#    #+#             */
/*   Updated: 2023/06/02 18:38:20 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	left_pipe(t_commands *commands, int pipedes[2])
{
	close(STDOUT_FILENO);
	dup(pipedes[1]); //duplicates the write end of the left side of pipe
	close(pipedes[0]);
	close(pipedes[1]);
	//function to exec commands, should be parser or process_tokens?
	process_tokens(commands);
}

static void	right_pipe(t_commands *commands, int pipedes[2])
{
	close(STDIN_FILENO);
	dup(pipedes[0]); //duplicates the read end of the right side of pipe
	close(pipedes[0]);
	close(pipedes[1]);
	//function to exec commands, should be parser or process_tokens?
	process_tokens(commands);
}

static void error_message(int error, char *mes)
{
	printf("%s\n", mes);
	exit(error);
}

static void	exec_pipe(int pipedes[4], int i, int size, t_commands *commands)
{
	pid_t	child;

	child = fork();
	if (child == -1)
		error_message(EXIT_FAILURE, PF);
	else if (child == 0)
	{
		if (i > 0)
			left_pipe(commands, pipedes);
		if (i < size - 1)
			right_pipe(commands, pipedes);
		parser(commands);
	}
	else
	{
		if (i > 0) {
			close(pipedes[0]);
			close(pipedes[1]);
		}
		if (i < size - 1) {
			pipedes[0] = pipedes[2];
			pipedes[1] = pipedes[3];
		}
	}
}

void	open_pipe(t_commands *commands)
{
	int		pipedes[4];
	int		size;
	int		i;

	i = -1;
	pipedes[0] = 0;
	pipedes[1] = 0;
	size = lstsize_commands(commands);
	while (++i < size)
	{
		if (i < size - 1 && (pipe(pipedes) == -1))
		{
			printf(PF);
			exit(EXIT_FAILURE);
		}
		exec_pipe(pipedes, i, size, commands);
		commands = commands->next;
	}
	i = -1;
	while (++i < size)
		wait(NULL);
	/* if (pipe(pipedes) == -1) //create a pair of fd 
	{
		printf("pipe() failed\n");
		exit(g_exit_status);
	}
	if (child == -1)
	{
		printf("%s\n", FF);
		exit(g_exit_status);
	}
	if (child == 0) //means we are in the child process
		left_pipe(commands, pipedes);
	right_pipe(commands->next, pipedes);
	close(pipedes[0]);
	close(pipedes[1]);
	waitpid(child, &temp, 0); //parent waits for child to finish */
	/* g_exit_status = temp >> 8; */
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