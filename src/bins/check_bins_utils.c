/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bins_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:22:14 by mrichard          #+#    #+#             */
/*   Updated: 2023/08/08 16:58:11 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(t_env *env)
{
	char	**path;
	char	*value;

	value = env_value("PATH", env);
	if (value)
	{
		path = ft_split(value, ':');
		free(value);
		return (path);
	}
	free(value);
	return (NULL);
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

void	check_heredoc(t_tokens *token)
{
	int			fd;
	t_tokens	*head;

	head = token;
	while (token)
	{
		if (!token->skip && token->type == HEREDOC && token->next)
		{
			heredoc_while(token->next->str);
			fd = open("/tmp/1", O_RDONLY, 0644);
			dup2(fd, STDIN_FILENO);
			unlink("/tmp/1");
			token->skip = 1;
		}
		token = token->next;
	}
}
