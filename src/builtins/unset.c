/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 20:23:02 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/07 21:46:56 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_env(t_commands *command)
{
	t_env	*prev;
	t_env	*curr;
	size_t	var_len;

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
			if (curr->was_added)
				free(curr->str);
			free(curr);
			return (1);
		}
		prev = curr;
		curr = prev->next;
	}
	return (0);
}
