/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:57:17 by mrichard          #+#    #+#             */
/*   Updated: 2023/03/01 20:41:20 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_len(char **envp)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (envp[++i])
		count++;
	return (count);	
}

static int	is_executable(char *bin_path, struct stat f, char **line)
{
	if (f.st_mode & __S_IFREG)
	{
		if (f.st_mode & S_IXUSR)
			return (run_cmd(bin_path, line));
		else 
		{
			printf("minishell: permission denied: ");
			printf("%s\n", bin_path);
		}
		free(bin_path);
		return (1);
	}
	free(bin_path);
	return (0);
}

int	check_bins(char **line)
{
	int			i;
	char		*bin_path;
	char		**path;
	struct stat	f;	
	
	path = ft_split(get_env_var("PATH"), ':');
	i = -1;
	while (path && path[++i])
	{
		if (ft_start_with(line[0], path[i]))
			bin_path = ft_strdup(line[0]);
		/* else
			bin_path = ft_pathjoin(path[i], line[0]); */
		if (lstat(bin_path, &f) == -1)
			free(bin_path);
		else
		{
			ft_free(path);
			return (is_executable(bin_path, f, line));
		}
	}
	ft_free(path);
	return (0);
}

void    init_env(char **envp)
{
	int	i;

	i = -1;
	global_env = (char **)malloc(sizeof(char *) * (env_len(envp) + 1));
	while (envp[++i])
	{
		if (!(global_env[i] = ft_strdup(envp[i])))
			exit_and_free();
	}
}

int	run_cmd(char *path, char **args)
{
	pid_t	pid;

	pid = fork();
	signal(SIGINT, proc_signal_handler);
	if (pid == 0)
		execve(path, args, global_env);
	else if (pid < 0)
	{
		free(path);
		printf("Fork failed to create a new process.");
		return (-1);
	}
	wait(&pid);
	if (path)
		free(path);
	return (1);
}

