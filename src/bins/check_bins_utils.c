/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bins_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:22:14 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/01 22:46:59 by mrichard         ###   ########.fr       */
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

int	parse_error(char *bin_path)
{
	free(bin_path);
	g_exit_status = 1;
	printf("%s\n", CPARSE);
	return (ERROR);
}

void	delete_char(t_tokens *node)
{
	char	*new_file;
	
	if (node->str[0] == PLICAS)
		new_file = ft_strtrim(node->str, "'");
	else
		new_file = ft_strtrim(node->str, "\"");
	free(node->str);
	node->str = new_file;
}

int	check_awk(t_tokens *token, char *bin_path)
{
	t_tokens *node;
	
	node = token;
	if (!ft_strcmp(node->str, "awk") || !ft_strcmp(node->str, "gawk"))
	{
		node = node->next;
		if (node->next->type == OPTION)
			node = node->next;
		if (node->str[0] == '{')
			return (parse_error(bin_path));
		if (node->str[0] == PLICAS && node->str[ft_strlen(node->str) - 1] == PLICAS)
		{
			node->str[0] = '"';
			node->str[ft_strlen(node->str) - 1] = '"';
		}
		if (node->next && isquote(node->next->str[0])
			&& isquote(node->next->str[ft_strlen(node->next->str) - 1]))
			delete_char(node->next);
	}
	return (0);
}
