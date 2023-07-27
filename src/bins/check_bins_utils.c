/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bins_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:22:14 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/27 19:36:10 by mrichard         ###   ########.fr       */
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

int	is_input_command(char *str)
{
	if (!ft_strcmp(str, "cat"))
		return (1);
	if (!ft_strcmp(str, "wc"))
		return (1);
	return (0);
}

int	is_specific_command(t_tokens *token)
{
	if (is_input_command(token->str))
	{
		if (token->next && token->next->type == HEREDOC)
			return (1);
	}
	return (0);
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
			printf("is 2: %d\n", is_specific_command(head));
			if (is_specific_command(head))
				dup2(fd, STDIN_FILENO);
			unlink("/tmp/1");
			token->skip = 1;
		}
		token = token->next;
	}
}
