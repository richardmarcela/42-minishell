/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_token_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 16:29:54 by riolivei          #+#    #+#             */
/*   Updated: 2023/07/26 20:11:38 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_content(char *str, int ipos, int fpos)
{
	while (++ipos < fpos)
	{
		if (!isquote(str[ipos]))
			return (1);
	}
	return (0);
}

int	is_option(char *str)
{
	int	i;

	i = 0;
	while (isquote(str[i]))
		i++;
	if (str[i] == '-' && !has_content(str, 0, i))
	{
		if (has_content(str, i, ft_strlen(str)))
			return (1);
		i++;
	}
	return (0);
}

int	is_pipe(char *str)
{
	if (*str == '|')
		return (1);
	return (0);
}

int	is_redirect(char *str, int was_quoted)
{
	if (str && !was_quoted)
	{
		if (!ft_strcmp(str, "<"))
			return (1);
		if (!ft_strcmp(str, ">"))
			return (1);
		if (!ft_strcmp(str, "<<"))
			return (1);
		if (!ft_strcmp(str, ">>"))
			return (1);
		return (0);
	}
	return (0);
}
