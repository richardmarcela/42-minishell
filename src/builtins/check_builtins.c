/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 22:46:03 by riolivei          #+#    #+#             */
/*   Updated: 2023/07/26 16:03:21 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include "minishell.h"

int	check(t_commands *command)
{
	if (command->token->str == NULL)
		return (0);
	if (!ft_strcmp(command->token->str, "exit"))
		return (exit_terminal(command));
	if (!ft_strcmp(command->token->str, "env"))
		return (env(command->env, 0));
	if (!ft_strcmp(command->token->str, "unset"))
		return (unset(command->token, command->env));
	if (!ft_strcmp(command->token->str, "export"))
	{
		if (command->token->next)
		{
			command->token = command->token->next;
			export(command);
			return (1);
		}
		return (env(command->env, 1));
	}
	if (!ft_strcmp(command->token->str, "cd"))
		return (change_dir(command->token, command->env));
	return (0);
}

int	check_builtins(t_commands *command)
{
	char	value[PATH_MAX];

	if (command->token->str == NULL)
		return (0);
	if (!ft_strcmp(command->token->str, "echo"))
		return (print(command->token->next));
	if (!ft_strcmp(command->token->str, "$?"))
	{
		printf("%lld: %s\n", g_exit_status, CNF);
		g_exit_status = 127;
		return (1);
	}
	if (!ft_strcmp(command->token->str, "pwd"))
	{
		printf("%s\n", getcwd(value, PATH_MAX));
		return (1);
	}
	return (0);
}
