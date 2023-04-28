/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:26:06 by riolivei          #+#    #+#             */
/*   Updated: 2023/04/28 22:58:22 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**fill_ops(void)
{
	char	**ops;

	ops = (char **)malloc(sizeof(char *) * 7);
	ops[0] = "|";
	ops[1] = "<";
	ops[2] = ">";
	ops[3] = "<<";
	ops[4] = ">>";
	ops[5] = "<>";
	ops[6] = 0;
	return	(ops);
}

static void	adding_new_token(t_tokens *token, int pos)
{
	char		*temp_str;
	t_tokens	*new_token;
	t_tokens	*temp_next;

	temp_str = token->str;
	temp_next = token->next;
	token->str = ft_substr(token->str, 0, pos);
	new_token = lstnew_token(temp_str, PIPE);
	token->next = new_token;
	new_token = temp_next;
}

static void	check_tokens(t_tokens *token)
{
	int	i;
	int pos;
	char **ops;
	t_tokens	*head = token;

	ops = fill_ops();
	while (token)
	{
		i = -1;
		printf("TOKEN Q ENTROU: %s\n", token->str);
		while (ops[++i])
		{
			pos = search_ops_in_str(token->str, ops[i], ft_strlen(token->str));
			printf("POS: %d - CHAR: %s\n", pos, ops[i]);
			if (pos > -1 && !has_open_quotes(token->str, pos))
			{
				/* printf("CHAR Q SAIU: %s\n", ops[i]);
				exit(0); */
				adding_new_token(token, pos);
			}
		}
		token = token->next;
	}
	while (head)
	{
		printf("TOKEN: %s\n", head->str);
		head = head->next;
	}
}

int		process_tokens(t_tokens *token, char **envp)
{
	struct stat	f;

	while (token)
	{
		if (has_unclosed_quotes(token))
			return (ERROR);
		/* DO WE REALLY NEED THIS?
		if (token->type == SETTING && lstsize_tokens(token) == 1)
		{
			//se tiver a dar set a uma variavel
			//faz merdas e avanca nos tokens
			token = token->next;
		} */
		if (check_builtins(token, envp)  || check_bins(token, envp))
			return (1);
		if (lstat(token->str, &f) != -1)
		{
			if (f.st_mode & __S_IFDIR)
			{
				token = token->next;
				/* change_dir(token->str); */
				return (1);
			}	
			if (f.st_mode & S_IXUSR)
				return(run_cmd("", token, envp)); //sending an empty string just for the program to work
		}
		token = token->next;
	}
	return (1);
}

void	parser(t_commands *commands)
{
	while (commands)
	{
		check_tokens(commands->token);
		if (process_tokens(commands->token, commands->envp) == ERROR)
		{
			readline(EPROMPT);
			break ;
		}
		commands = commands->next;
	}
}
