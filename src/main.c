/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:53:02 by mrichard          #+#    #+#             */
/*   Updated: 2023/04/06 20:50:11 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//LINE E A LINHA INTEIRA

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char  *line;

	(void)argv;
	if (argc == 1)
	{
		while (1)
		{
			line = readline(PROMPT);
			pipe_commands(line, envp);
			add_history(line);
			free(line);
		}
	}
	else
		printf("Error: Too many arguments!\n");
	return (0);
}