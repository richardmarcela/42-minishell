/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 22:47:59 by riolivei          #+#    #+#             */
/*   Updated: 2023/06/09 17:06:42 by mrichard         ###   ########.fr       */
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
		{
			g_exit_status = 126;
			printf("%s\n", PD);
		}
	}
	free(bin_path);
	return (0);
}

int	check_bins(t_tokens *token, t_env *env)
{
	int			i;
	char		*bin_path;
	char		**path;
	struct stat	f;
	t_tokens	*head;

	path = ft_split(env_value("PATH", env), ':');
	i = -1;
	head = token;
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
	char		**args;
	char		**env_matrix;
	pid_t		pid;

	args = fill_args(token);
	env_matrix = fill_env_matrix(env);
	pid = fork();
	handle_cmd_signals();
	if (pid == 0)
	{
		if (lstsize_tokens(token, 1) != lstsize_tokens(token, 0))
			handle_redir(token, bin_path, args, env_matrix);
		execve(bin_path, args, env_matrix);
	}
	if (pid < 0)
	{
		free(bin_path);
		g_exit_status = 1;
		printf("%s\n", FF);
		return (0);
	}
	wait(&pid);
	handle_global_signals();
	return (1);
}
