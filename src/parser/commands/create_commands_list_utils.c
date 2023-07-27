/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands_list_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:30:09 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/27 13:52:36 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute(t_commands *command, int flag)
{
	while (command)
	{
		if (flag == 1)
			check_heredoc(command->token);
		else
			files_exist(command->token, 1);
		command = command->next;
	}
}

void	remake_commands(t_commands *commands)
{
	t_commands	*head;

	head = commands;
	execute(head, 1);
	execute(head, 2);
}
