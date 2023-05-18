/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 22:09:34 by mrichard          #+#    #+#             */
/*   Updated: 2023/05/18 16:42:51 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  env_exists(t_commands *command, t_env *head)
{
	int     res;
	int     pos1;
	int     pos2;
	char    *input;
	char    *env_name;

	res = 0;
	pos1 = search_ops_in_str(command->token->str, "=", ft_strlen(command->token->str));
	input = ft_substr(command->token->str, 0, pos1);
	while (head)
	{
		pos2 = search_ops_in_str(head->str, "=", ft_strlen(head->str));
		env_name = ft_substr(head->str, 0, pos2);
		if (!ft_strcmp(input, env_name))
		{
			head->str = command->token->str;
			if (strchr(command->token->str, '$'))
				head->str = process_env_variable(command->token->str, command->env);
			res = 1;
			break;
		}
		head = head->next;
	}
	return (res);
}

int    export(t_commands *command)
{
	t_env   *new;
	t_env   *env_head;
	char	*env_value;
	
	env_head = command->env;
	if (ft_strchr(command->token->str, '='))
	{
		if (!env_exists(command, env_head))
		{
			env_value = command->token->str;
			if (strchr(command->token->str, '$'))
				env_value = process_env_variable(command->token->str, command->env);
			new = lstnew_env(env_value);
			lstadd_back_env(&command->env, new);
		}
	}
	return (1);
}