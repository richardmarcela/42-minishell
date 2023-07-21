/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:52:45 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/21 16:32:26 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lstsize_tokens(t_tokens *token, int filter)
{
	int			count;
	t_tokens	previous;

	count = 0;
	previous = *token;
	while (token)
	{
		if (filter)
		{
			if (!is_redirect(token->str) && !is_redirect(previous.str))
				count++;
			previous = *token;
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

int	search_ops_in_str(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s1[++i])
	{
		if (s1[i] == s2[0])
		{
			if (ft_strlen(s2) > 1)
			{
				if (s1[i + 1] == s2[1])
					return (i);
				break ;
			}
			else
			{
				if (s1[i + 1] != s2[0])
					return (i);
				break ;
			}
		}
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
