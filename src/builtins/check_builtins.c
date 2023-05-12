/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 22:46:03 by riolivei          #+#    #+#             */
/*   Updated: 2023/05/12 15:32:33 by mrichard         ###   ########.fr       */
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
	else if (!ft_strcmp(command->token->str, "env"))
		return (env(command->env));
	else if (!ft_strcmp(command->token->str, "unset"))
	{
		command->token = command->token->next;
		return (unset_env(command));
	}
	else if (!ft_strcmp(command->token->str, "exit"))
		exit(0);
	return (0);
}