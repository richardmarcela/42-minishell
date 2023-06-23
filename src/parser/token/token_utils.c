/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:20:33 by mrichard          #+#    #+#             */
/*   Updated: 2023/06/23 17:49:03 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
