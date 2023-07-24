/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 20:23:02 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/24 21:29:42 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_env(t_tokens *token, t_env *env)
{
	t_env	*prev;
	t_env	*curr;
	size_t	var_len;

	var_len = ft_strlen(token->str);
	prev = NULL;
	curr = env;
	while (curr)
	{
		if (!ft_strncmp(token->str, curr->str, var_len))
		{
			if (!prev)
				env = curr->next;
			else
				prev->next = curr->next;
			if (curr->was_added)
				free(curr->str);
			free(curr);
			break ;
		}
		prev = curr;
		curr = prev->next;
	}
}

int	unset(t_tokens *token, t_env *env)
{
	if (!token->next)
		return (printf("not enough arguments\n"));
	token = token->next;
	while (token)
	{
		unset_env(token, env);
		token = token->next;
	}
	return (1);
}