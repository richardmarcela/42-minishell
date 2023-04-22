/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:51:42 by riolivei          #+#    #+#             */
/*   Updated: 2023/04/21 20:46:28 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int isquote(int c)
{
	if (c == ASPAS || c == PLICAS)
		return 1;
	return 0;
}

int	has_empty_pipe(char **splitted)
{
	int	i;
	char *temp;
	
	i = -1;
	while (splitted[++i])
	{
		temp = ft_strtrim(splitted[i], " ");
		if (!temp)
			return (1);
		if (!ft_strlen(temp))
			return (1);
	}
	return (0);
}

/* void    ft_free(t_command_line *command)
{
    free(command->str);
} */
