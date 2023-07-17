/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:52:45 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/17 21:52:47 by mrichard         ###   ########.fr       */
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
	int		j;
	int		flag;

	i = -1;
	while (splitted[++i])
	{
		flag = 0;
		j = -1;
		while (splitted[i][++j])
			if (splitted[i][j] != ' ')
				flag = 1;
		if (!flag)
		{
			i = -1;
			while (splitted[++i])
				free(splitted[i]);
			free(splitted);
			return (1);
		}
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
