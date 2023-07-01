/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:53:02 by mrichard          #+#    #+#             */
/*   Updated: 2023/06/30 15:38:16 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	g_exit_status = 0;

void	check_line(char *line)
{
	if (!line)
	{
		g_exit_status = 0;
		exit(0);
	}
}

int	main(int argc, char **argv, char **envp)
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
			check_line(line);
			line = ft_strtrim(line, " ");
			if (ft_strlen(line))
			{
				pipe_commands(line, env);
				add_history(line);
			}
			free(line);
		}
	}
	else
		printf("Error: Too many arguments!\n");
	return (0);
}
