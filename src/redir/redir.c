/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:10:39 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/23 20:46:46 by mrichard         ###   ########.fr       */
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
		if (token->type == RED_IN)
		{
			fd = open(token->next->str, O_RDONLY, 0644);
			if (fd < 0)
			{
				res = 0;
				printf("%s: %s\n", token->next->str, UNKNOWN);
				break ;
			}
		}
		token = token->next;
	}
	token = head;
	return (res);
}

static void	heredoc_while(char *delim)
{
	char	*delim_line;
	int		fd;
	int		output;
	char	buff[4095];

	write(0, "> ", 2);
	delim_line = ft_strjoin(delim, "\n");
	fd = open("/tmp/1", O_RDWR | O_CREAT | O_TRUNC, 0644);
	output = read(0, buff, 4095);
	printf("output: %d\n", output);
	while (output > 0)
	{
		printf("ENTROU CICLO\n");
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

static void	in(t_TokenType type, char *input_file)
{
	int		fd;

	if (type == HEREDOC)
	{
		printf("ENTROU AQUI CRL\n");
		heredoc_while(input_file);
		fd = open("/tmp/1", O_RDONLY, 0644);
	}
	else
		fd = open(input_file, O_RDONLY, 0644);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (type == HEREDOC)
		unlink("/tmp/1");
}

void	handle_redir(t_tokens *token)
{
	while (token)
	{
		if (is_redirect(token->str))
		{
			if (token->type == APPEND_OUT || token->type == RED_OUT)
				out(token->type, token->next->str);
			else
				in(token->type, token->next->str);
		}
		token = token->next;
	}
}
