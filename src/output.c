/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:55:19 by riolivei          #+#    #+#             */
/*   Updated: 2023/03/11 20:14:40 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//printa o output resultante do comando, se este for válido
void	output(char *command)
{
	char	**line;
	int		i;

	i = -1;
	
	/* if (check_pipes(line))
		pipes(); */
	line = ft_split(command, ' ');
	while (line[++i])
	{
		if (!check_command(line[i]))
		{
			echo_error();
			return ;
		}
	}
	if (!processing(line))
		printf("%s: %s\n", CNF, line[0]);

}
