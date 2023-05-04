/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 22:46:03 by riolivei          #+#    #+#             */
/*   Updated: 2023/05/04 22:34:45 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_commands *command)
{    
	if (!ft_strcmp(command->token->str, "echo"))
		return (print(command->token->next));
	else if (!ft_strcmp(command->token->str, "cd"))
    {
        command->token = command->token->next;
		return (change_dir(command->token->str));
    }
	else if (!ft_strcmp(command->token->str, "pwd"))
	{
		printf("%s\n", getcwd(getenv("PWD"), 1000));
		return (1);
	}
	else if (!ft_strcmp(command->token->str, "export"))
	{
		command->token = command->token->next;
		return (export(command));
	}
	/* else if (!ft_strcmp(line[0], "unset"))
		unsetenv();
	[TIREI DAQUI O ENV PQ E UM BINARIO] */
	return (0);
}