/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:43:41 by riolivei          #+#    #+#             */
/*   Updated: 2023/03/05 18:50:48 by riolivei         ###   ########.fr       */
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
		command = ft_strtrim(readline(PROMPT), " ");
		if (!command)
		{
			free(command);
			continue ;
		}
		else if (!ft_strcmp(command, "exit")) //fecha o programa sem '\n'
			break ;
		add_history(command);
		output(command);
		free(command);
	}
	return (0);
}
