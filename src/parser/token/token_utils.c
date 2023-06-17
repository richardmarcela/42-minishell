/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:20:33 by mrichard          #+#    #+#             */
/*   Updated: 2023/06/17 20:42:34 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*define_head(char **splitted, int *i)
{
	t_tokens	*head;
	t_tokens	*current_node;

	if (ft_strchr(splitted[0], '=') != NULL)
	{
		head = lstnew_token(splitted[(*i)++], SETTING);
		if (splitted[(*i)])
		{
			current_node = head;
			current_node = current_node->next;
			current_node = lstnew_token(splitted[(*i)], COMMAND);
			lstadd_back_token(&head, current_node);
		}
	}
	else
		head = lstnew_token(splitted[(*i)], COMMAND);
	return (head);
}

static int	red_count(char *str, int c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == c)
			count++;
	}
	return (count);
}

t_TokenType	which_red(char *str)
{
	if (red_count(str, '>') == 1 && red_count(str, '<') == 1)
		return (IN_OUT);
	if (red_count(str, '>') == 1)
		return (RED_OUT);
	if (red_count(str, '<') == 1)
		return (RED_IN);
	if (red_count(str, '>') == 2 && red_count(str, '<') == 0)
		return (APPEND_OUT);
	if (red_count(str, '<') == 2 && red_count(str, '>') == 0)
		return (APPEND_IN);
	return (ERRO);
}
