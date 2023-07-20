/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:51:41 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/20 18:35:03 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_tokens *token)
{
	int			size;
	int			i;
	t_tokens	*node;

	i = -1;
	size = lstsize_tokens(token, 0);
	while (++i < size)
	{
		node = token;
		token = token->next;
		printf("token str: %s\n", node->str);
		if (ft_strcmp(node->str, "$"))
			free(node->str);
		free(node);
	}
}

void	free_env(t_env *env)
{
	int		i;
	int		size;
	t_env	*node;

	i = -1;
	size = env_len(env);
	while (++i < size)
	{
		node = env;
		env = env->next;
		if (node->was_added)
			free(node->str);
		free(node);
	}
}

void	free_structs(t_commands *commands, int flag)
{
	int			size;
	int			i;
	t_commands	*node;

	i = -1;
	if (flag)
		free_env(commands->env);
	size = lstsize_commands(commands);
	while (++i < size)
	{
		node = commands;
		free_tokens(commands->token);
		commands = commands->next;
		free(node);
	}
}
