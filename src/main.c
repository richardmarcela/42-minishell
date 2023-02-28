/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:43:41 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/28 18:04:24 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*command;

	while (1)
	{
		command = readline(PROMPT);
		if (!command) //acontece no CTRL+D e fecha o programa
		{
			free(command);
			printf("\n");
			break ;
		}
		else if (!ft_strcmp(command, "exit")) //fecha o programa sem '\n'
			break ;
		add_history(command);
		output(command);
		free(command);
	}
	return (0);
}
