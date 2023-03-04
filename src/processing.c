/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:01:11 by riolivei          #+#    #+#             */
/*   Updated: 2023/03/04 19:52:08 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_builtins(char **line)
{
	char	*pwd;
	
	if (!ft_strcmp(line[0], "echo"))
		return (print(line));
	else if (!ft_strcmp(line[0], "cd"))
		return (change_dir(line[1]));
	else if (!ft_strcmp(line[0], "pwd"))
	{
		pwd = current_directory();
		printf("%s\n", pwd);
		free(pwd);
		return (1);
	}
	/* else if (!ft_strcmp(line[0], "setenv"))
		setenv();
	else if (!ft_strcmp(line[0], "unsetenv"))
		unsetenv();
	else if (!ft_strcmp(line[0], "env"))
		print_env(); */
	return (0);
}

//identifica o comando e o que deve fazer a seguir
int	processing(char **line)
{
	struct stat	f;

	if (check_builtins(line) || check_bins(line))
		return (1);
	if (lstat(line[0], &f) != -1)
	{
		if (f.st_mode & __S_IFDIR)
		{
			change_dir(line[1]);
			return (1);
		}		
		if (f.st_mode & S_IXUSR)
			return(run_cmd(ft_strdup(line[0]), line));
	}
	return (0);
}
