/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:10:39 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/20 18:28:11 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	out(int fd, t_TokenType type, char *output_file)
{
	if (type == APPEND_OUT)
		fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	return (fd);
}

int	in(int fd, t_TokenType type, char *input_file)
{
	if (type == APPEND_IN)
		fd = open(input_file, O_RDONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(input_file, O_RDONLY, 0644);
	dup2(fd, STDIN_FILENO);
	return (fd);
}

void	handle_redir(t_tokens *token)
{
	int			fd;

	while (token)
	{
		if (is_redirect(token->str))
		{
			if (token->type == APPEND_OUT || token->type == RED_OUT)
				fd = out(fd, token->type, token->next->str);
			else
				fd = in(fd, token->type, token->next->str);
		}
		token = token->next;
	}
	close(fd);
}
