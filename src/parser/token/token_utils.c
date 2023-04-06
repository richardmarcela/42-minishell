/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:20:33 by mrichard          #+#    #+#             */
/*   Updated: 2023/04/06 18:16:16 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int token_check_builtins(char *str)
{
	int res;

	res = 0;
	if (!ft_strcmp(str, "echo"))
		res = 1;
	else if (!ft_strcmp(str, "cd"))
		res = 1;
	else if (!ft_strcmp(str, "pwd"))
		res = 1;
	else if (!ft_strcmp(str, "unset"))
		res = 1;
	else if (!ft_strcmp(str, "export"))
		res = 1;
	return (res);
}

int token_check_bins(char *str)
{
	int			i;
	char		*bin_path;
	char		**path;
	struct stat	f;

	path = ft_split(getenv("PATH"), ':');
	i = -1;
	while (path && path[++i])
	{
		bin_path = ft_strjoin(ft_strjoin(path[i], "/"), str);
	}
}