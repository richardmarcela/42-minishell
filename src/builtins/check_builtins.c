/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 22:46:03 by riolivei          #+#    #+#             */
/*   Updated: 2023/05/27 17:50:07 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_commands *command)
{
	if (!ft_strcmp(command->token->str, "echo"))
		return (print(command->token->next, command->env));
	else if (!ft_strcmp(command->token->str, "cd"))
	{
		command->token = command->token->next;
		return (change_dir(command->token->str, command->env));
	}
	else if (!ft_strcmp(command->token->str, "pwd"))
	{
		printf("%s\n", getcwd(env_value("PWD", command->env), 1000));
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
		return (exit_terminal(command->token));
	else if (!ft_strcmp(command->token->str, "$?"))
	{
		printf("%lld\n", g_exit_status);
		return (1);
	}
	return (0);
}
