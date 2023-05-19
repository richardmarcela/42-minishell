/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:53:02 by mrichard          #+#    #+#             */
/*   Updated: 2023/05/19 19:46:26 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env		*env;
	
	(void)argv;
	handle_global_signals();
	if (argc == 1)
	{
		env = init_env(envp);
		while (1)
		{
			line = readline(PROMPT);
			if (!line)
				exit(0);
			pipe_commands(line, env);
			add_history(line);
			free(line);
		}
	}
	else
		printf("Error: Too many arguments!\n");
	return (0);
}