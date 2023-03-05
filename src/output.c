/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:55:19 by riolivei          #+#    #+#             */
/*   Updated: 2023/03/05 18:54:18 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//printa o output resultante do comando, se este for válido
void	output(char *command)
{
	char	**line;

	/* if (check_pipes(line))
		pipes(); */
	line = ft_split(command, ' ');

	if (!processing(line))
		printf("%s: %s\n", CNF, line[0]);

}
