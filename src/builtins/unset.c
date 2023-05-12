/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 20:23:02 by mrichard          #+#    #+#             */
/*   Updated: 2023/05/12 16:07:09 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    free_env_var(t_env *env)
{
	free(env->str);
	free(env);
}

int unset_env(t_commands *command)
{
	t_env   *prev;
	t_env   *curr;
	size_t  var_len;

	var_len = ft_strlen(command->token->str);
	// Caso a variável a ser removida seja a primeira da lista
	if (!ft_strncmp(command->token->str, command->env->str, var_len))
	{
		curr = command->env;
		command->env = curr->next;
		free_env_var(curr);
		return (1);
	}
	prev = command->env;
	curr = prev->next;
	while (curr)
	{
		if (!ft_strncmp(command->token->str, curr->str, var_len))
		{
			prev->next = curr->next;
			free_env_var(curr);
			return (1);
		}
		prev = curr;
		curr = prev->next;
	}
	return (0);
}
