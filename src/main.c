/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:43:41 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/28 05:24:51 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*command;
	char	**line;

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
		line = ft_split(command, ' ');
		output(line);
		free(command);
		free(line);
	}
	return (0);
}
