/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:53:02 by mrichard          #+#    #+#             */
/*   Updated: 2023/05/05 19:34:46 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env		*env;
	
	(void)argv;
	if (argc == 1)
	{
		env = init_env(envp);
		while (1)
		{
			line = readline(PROMPT);
			pipe_commands(line, env);
			add_history(line);
			free(line);
		}
	}
	else
		printf("Error: Too many arguments!\n");
	return (0);
}