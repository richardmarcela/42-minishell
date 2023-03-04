/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:01:11 by riolivei          #+#    #+#             */
/*   Updated: 2023/03/03 18:02:01 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_builtins(char **line)
{
	char	*pwd;
	
	if (!ft_strcmp(line[0], "cd"))
		change_dir(line[1]);
	else if (!ft_strcmp(line[0], "pwd"))
	{
		pwd = current_directory();
		printf("%s\n", pwd);
		free(pwd);
	}
	/* else if (!ft_strcmp(line[0], "setenv"))
		setenv();
	else if (!ft_strcmp(line[0], "unsetenv"))
		unsetenv();
	else if (!ft_strcmp(line[0], "env"))
		print_env(); */
	return (1);
}

//identifica o comando e o que deve fazer a seguir
int	processing(char **line)
{
	struct stat	f;
	int			is_builtin;

	if ((is_builtin = check_builtins(line)) == 1 || check_bins(line))
		return (0);
	if (is_builtin < 0)
		return (-1);
	if (lstat(line[0], &f) != -1)
	{
		if (f.st_mode & S_IXUSR)
			return(run_cmd(ft_strdup(line[0]), line));
	}
	return (0);
}
