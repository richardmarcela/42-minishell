/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bins_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:22:14 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/26 16:18:27 by mrichard         ###   ########.fr       */
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

int	total_heredocs(t_tokens *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == HEREDOC)
			count++;
		token = token->next;
	}
	return (count);
}

void	check_heredoc(t_tokens *token)
{
	int			count_heredocs;
	int			i;

	i = 0;
	count_heredocs = total_heredocs(token);
	while (token)
	{
		if (token->type == HEREDOC)
		{
			i++;
			if (i == count_heredocs)
			{
				heredoc_while(token->next->str);
				unlink("/tmp/1");
				break ;
			}
		}
		token = token->next;
	}
}
