/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:43:41 by riolivei          #+#    #+#             */
/*   Updated: 2023/03/01 19:52:31 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **global_env;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*command;

	init_env(envp);
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
