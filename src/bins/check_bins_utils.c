/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bins_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:22:14 by mrichard          #+#    #+#             */
/*   Updated: 2023/06/23 18:26:12 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(t_env *env)
{
	char	**path;
	char	*value;

	value = env_value("PATH", env);
	path = ft_split(value, ':');
	free(value);
	return (path);
}

char	*get_bin_path(char *path, char *str)
{
	char	*bin_path;
	char	*small_bin_path;

	small_bin_path = ft_strjoin(path, "/");
	bin_path = ft_strjoin(small_bin_path, str);
	free(small_bin_path);
	free(path);
	return (bin_path);
}