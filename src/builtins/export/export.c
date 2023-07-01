/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 22:09:34 by mrichard          #+#    #+#             */
/*   Updated: 2023/06/29 18:26:55 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	*attr_values_quotes(void)
{
	bool	*quotes;

	quotes = malloc(sizeof(bool) * 2);
	quotes[0] = false;
	quotes[1] = false;
	return (quotes);
}

static int	env_exists(t_env *head, char *new_env, char *env_value)
{
	int		pos;
	char	*env_name;

	while (head)
	{
		pos = search_ops_in_str(head->str, "=", ft_strlen(head->str));
		env_name = ft_substr(head->str, 0, pos);
		if (!ft_strcmp(new_env, env_name))
		{
			head->str = env_value;
			free(env_name);
			return (1);
		}
		head = head->next;
		free(env_name);
	}
	return (0);
}

int	export(t_commands *command)
{
	t_env	*new;
	t_env	*env_head;
	int		pos;
	char	*env_value;
	char	*env_name;

	env_head = command->env;
	if (ft_strchr(command->token->str, '='))
	{
		pos = search_ops_in_str(command->token->str, "=",
				ft_strlen(command->token->str));
		env_name = ft_substr(command->token->str, 0, pos);
		env_value = process_env_variable(command->token->str, command->env);
		if (!env_exists(env_head, env_name, env_value))
		{
			new = lstnew_env(env_value);
			lstadd_back_env(&command->env, new);
		}
		free(env_name);
	}
	return (1);
}
