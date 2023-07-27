/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:10:39 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/27 18:31:07 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	files_exist(t_tokens *token)
{
	int			res;
	int			fd;
	t_tokens	*head;

	head = token;
	res = 1;
	while (token)
	{
		if (token->type == RED_IN && token->next)
		{
			fd = open(token->next->str, O_RDONLY, 0644);
			if (fd < 0)
			{
				res = 0;
				if (!token->skip)
					printf("%s: %s\n", token->next->str, UNKNOWN);
				token->skip = 1;
				break ;
			}
		}
		token = token->next;
	}
	token = head;
	return (res);
}

void	heredoc_while(char *delim)
{
	char	*delim_line;
	int		fd;
	int		output;
	char	buff[4095];

	write(0, "> ", 2);
	delim_line = ft_strjoin(delim, "\n");
	fd = open("/tmp/1", O_RDWR | O_CREAT | O_TRUNC, 0644);
	output = read(0, buff, 4095);
	while (output > 0)
	{
		buff[output] = '\0';
		if (!ft_strcmp(buff, delim_line))
			break ;
		ft_putstr_fd(buff, fd);
		write(0, "> ", 2);
		output = read(0, buff, 4095);
	}
	free(delim_line);
	close (fd);
}

static void	out(t_TokenType type, char *output_file)
{
	int	fd;

	if (type == APPEND_OUT)
		fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	in(char *input_file)
{
	int		fd;

	fd = open(input_file, O_RDONLY, 0644);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

int	handle_redir(t_tokens *token)
{
	t_TokenType	type;

	check_heredoc(token);
	if (!files_exist(token))
		return (0);
	while (token)
	{
		if (is_redirect(token->str, token->was_quoted))
		{
			type = token->type;
			if (type == APPEND_OUT || type == RED_OUT)
				out(type, token->next->str);
			else if (type == RED_IN)
				in(token->next->str);
		}
		token = token->next;
	}
	return (1);
}
