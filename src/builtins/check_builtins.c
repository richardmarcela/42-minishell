/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 22:46:03 by riolivei          #+#    #+#             */
/*   Updated: 2023/06/16 19:55:18 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check(t_commands *command)
{
	if (!ft_strcmp(command->token->str, "env"))
		return (env(command->env));
	else if (!ft_strcmp(command->token->str, "unset"))
		return (unset_env(command));
	else if (!ft_strcmp(command->token->str, "exit"))
		return (exit_terminal(command->token));
	else if (!ft_strcmp(command->token->str, "$?"))
	{
		printf("%lld: %s\n", g_exit_status, CNF);
		g_exit_status = 127;
		return (1);
	}
	return (0);
}

int	check_builtins(t_commands *command)
{
	if (!ft_strcmp(command->token->str, "echo"))
		return (print(command->token->next, command->env));
	else if (!ft_strcmp(command->token->str, "cd"))
		return (change_dir(command->token, command->env));
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
	return (check(command));
}
