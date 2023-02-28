/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:55:19 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/28 21:48:37 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//printa o output resultante do comando, se este for válido
void	output(char *command)
{
	char	**line;

	/* if (check_pipes(line))
		pipes(); */
	line = ft_split(command, ' ');
	if (!ft_strcmp(line[0], "echo"))
		print(command);
	else
	{
		if (!processing(line))
			printf("%s\n", CNF);
	}
}
