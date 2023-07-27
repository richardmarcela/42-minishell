/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands_list_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:30:09 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/27 19:36:08 by mrichard         ###   ########.fr       */
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
			files_exist(command->token);
		command = command->next;
	}
}

void	remake_commands(t_commands *commands)
{
	int			fd;
	t_commands	*head;


	fd = dup(STDIN_FILENO);
	head = commands;
	execute(head, 1);
	printf("is 1: %d\n", is_specific_command(head->token));
	if (is_specific_command(head->token))
		dup2(fd, STDIN_FILENO);
	execute(head, 2);
}
