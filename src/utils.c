/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:38:25 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/28 21:48:58 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*current_directory(void)
{
	char	*dir;

	dir = malloc(sizeof(char) * 200);
	return (getcwd(dir, 200));
}

int	count(char *command, int n)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (command[++i])
		if (command[i] == n)
			count++;
	return (count);
}
