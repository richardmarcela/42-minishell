/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 22:47:59 by riolivei          #+#    #+#             */
/*   Updated: 2023/06/17 22:09:05 by mrichard         ###   ########.fr       */
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
	char		*small_bin_path;
	char		**path;
	struct stat	f;
	t_tokens	*head;

	path = get_path(env);
	i = -1;
	head = token;
	while (path && path[++i])
	{
		small_bin_path = ft_strjoin(path[i], "/");
		bin_path = ft_strjoin(small_bin_path, head->str);
		free(small_bin_path);
		if (lstat(bin_path, &f) == -1)
			free(bin_path);
		else if (is_executable(bin_path, f))
		{
			free(path);
			return (run_cmd(bin_path, token, env));
		}
	}
	free(bin_path);
	free(path);
	return (0);
}

static int	free_values(char *bin_path, char **env_matrix, char **args)
{
	free(bin_path);
	free(env_matrix);
	free(args);
	g_exit_status = 1;
	printf("%s\n", FF);
	return (1);
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
			handle_redir(token);
		execve(bin_path, args, env_matrix);
	}
	if (pid < 0)
		return (free_values(bin_path, env_matrix, args));
	wait(&pid);
	free(args);
	free(env_matrix);
	return (1);
}
