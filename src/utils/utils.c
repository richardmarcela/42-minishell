/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:51:42 by riolivei          #+#    #+#             */
/*   Updated: 2023/07/15 16:46:57 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lstsize_tokens(t_tokens *token, int filter)
{
	int	count;

	count = 0;
	while (token)
	{
		if (filter)
		{
			if (is_redirect(token->str))
			{
				if (!ft_strcmp(token->str, "<") || !ft_strcmp(token->str, "<<"))
					count++;
				token = token->next;
			}
			else
				count++;
		}
		else
			count++;
		token = token->next;
	}
	return (count);
}

int	isquote(int c)
{
	if (c == ASPAS || c == PLICAS)
		return (1);
	return (0);
}

int	has_empty_pipe(char **splitted)
{
	int		i;
	char	*temp;

	i = -1;
	while (splitted[++i])
	{
		temp = ft_strtrim(splitted[i], " ");
		if (!temp || !ft_strlen(temp))
		{
			free(splitted);
			free(temp);
			return (1);
		}
		free(temp);
	}
	return (0);
}

int	search_ops_in_str(char *s1, char *s2, int n)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i] && i < n)
	{
		j = 0;
		while (s1[i + j] && s2[j]
			&& s1[i + j] == s2[j] && (i + j) < n)
		{
			if (s2[j + 1] == '\0')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

void	change_flag(bool *flag)
{
	if (!*flag)
		*flag = true;
	else
		*flag = false;
}
