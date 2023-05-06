/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 22:47:59 by riolivei          #+#    #+#             */
/*   Updated: 2023/05/05 20:27:17 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_len(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);	
}

static int	is_executable(char *bin_path, struct stat f)
{
	if (f.st_mode & __S_IFREG)
	{
		if (f.st_mode & S_IXUSR)
			return (1);
		else 
			printf("permission denied: %s\n", bin_path);
		free(bin_path);
		return (0);
	}
	free(bin_path);
	return (0);
}

int	check_bins(t_tokens *token, t_env *env)
{
	int			i;
	char		*bin_path;
	char		**path;
	struct 		stat	f;
	t_tokens	*head;
	t_tokens	*current;

	path = ft_split(getenv("PATH"), ':');
	i = -1;
	head = token;
	current = head;
	while (path && path[++i])
	{
		bin_path = ft_strjoin(ft_strjoin(path[i], "/"), head->str);
		if (lstat(bin_path, &f) == -1)
			free(bin_path);
		else if (is_executable(bin_path, f))
		{
			run_cmd(bin_path, token, env);
			return (1);
		}
	}
	return (0);
}

int	run_cmd(char *bin_path, t_tokens *token, t_env *env)
{
	char 		**args;
	char 		**env_matrix;
	pid_t		pid;

	args = fill_args(token);
	env_matrix = fill_env_matrix(env);
	pid = fork();
	signal(SIGINT, proc_signal_handler);
	if (pid == 0)
		execve(bin_path, args, env_matrix);
	if (pid < 0)
	{
		free(bin_path);
		printf("Fork failed to create a new process.\n");
		return (0);
	}
	wait(&pid);
	return (1);
}
