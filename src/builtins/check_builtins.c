/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 22:46:03 by riolivei          #+#    #+#             */
/*   Updated: 2023/06/29 15:15:42 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include "minishell.h"

static int	check(t_commands *command)
{
	if (!ft_strcmp(command->token->str, "env"))
		return (env(command->env));
	else if (!ft_strcmp(command->token->str, "unset"))
	{
		command->token = command->token->next;
		return (unset_env(command));
	}
	else if (!ft_strcmp(command->token->str, "exit"))
		return (exit_terminal(command));
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
	char	value[PATH_MAX];

	if (!ft_strcmp(command->token->str, "echo"))
		return (print(command->token->next, command->env));
	else if (!ft_strcmp(command->token->str, "cd"))
		return (change_dir(command->token, command->env));
	else if (!ft_strcmp(command->token->str, "pwd"))
	{
		printf("%s\n", getcwd(value, PATH_MAX));
		return (1);
	}
	else if (!ft_strcmp(command->token->str, "export"))
	{
		command->token = command->token->next;
		return (export(command));
	}
	return (check(command));
}
