/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 20:23:02 by mrichard          #+#    #+#             */
/*   Updated: 2023/06/16 19:21:06 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_env(t_commands *command)
{
	t_env	*prev;
	t_env	*curr;
	size_t	var_len;

	if (command->token->next)
		command->token = command->token->next;
	var_len = ft_strlen(command->token->str);
	prev = NULL;
	curr = command->env;
	while (curr)
	{
		if (!ft_strncmp(command->token->str, curr->str, var_len))
		{
			if (!prev)
				command->env = curr->next;
			else
				prev->next = curr->next;
			free(curr);
			return (1);
		}
		prev = curr;
		curr = prev->next;
	}
	return (1);
}
