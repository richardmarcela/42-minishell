/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:55:19 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/28 04:44:56 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//printa o output resultante do comando, se este for válido
void	output(char **line)
{
	if (!processing(line))
		printf("%s\n", CNF);
}
