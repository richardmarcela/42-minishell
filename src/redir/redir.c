/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:10:39 by mrichard          #+#    #+#             */
/*   Updated: 2023/06/01 21:47:56 by mrichard         ###   ########.fr       */
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

int	in(int fd, t_TokenType type, char *output_file)
{
	if (type == APPEND_IN)
		fd = open(output_file, O_RDONLY | O_CREAT | O_APPEND);
	else
		fd = open(output_file, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	return (fd);
}

void	handle_redir(t_tokens *token, char *bin_path,
	char **args, char **env_matrix)
{
	int	fd;

	(void)bin_path;
	(void)args;
	(void)env_matrix;
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
	/* execve(bin_path, args, env_matrix); */
	close(fd);
}
