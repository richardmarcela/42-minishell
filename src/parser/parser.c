/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:26:06 by riolivei          #+#    #+#             */
/*   Updated: 2023/05/04 22:34:49 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**fill_ops(void)
{
	char	**ops;

	ops = (char **)malloc(sizeof(char *) * 7);
	ops[0] = "<>";
	ops[1] = "<<";
	ops[2] = ">>";
	ops[3] = "<";
	ops[4] = ">";
	ops[5] = "|";
	ops[6] = NULL;
	return	(ops);
}

static void	adding_new_token(t_tokens *token, int pos, char *op)
{
	char		*original_str;
	char		*op_str;
	char		*new_str = NULL;
	t_tokens	*op_token;
	t_tokens	*new_token;

	if (ft_strlen(token->str) > ft_strlen(op)) //avoids some unnacessary tokens
	{
		original_str = token->str;
		op_str = ft_substr(original_str, pos, ft_strlen(op));
		token->str = ft_substr(original_str, 0, pos);
		new_str = ft_substr(original_str, pos + ft_strlen(op), ft_strlen(original_str) - ft_strlen(op_str) - ft_strlen(token->str));
		op_token = lstnew_token(op_str, PIPE);
		token->next = op_token;
		new_token = lstnew_token(new_str, PIPE);
		op_token->next = new_token;	
	}
}

static void	check_tokens(t_tokens *token)
{
	int	i;
	int pos;
	char **ops;

	ops = fill_ops();
	while (token)
	{
		i = -1;
		while (ops[++i])
		{
			pos = search_ops_in_str(token->str, ops[i], ft_strlen(token->str));
			if (pos > -1 && !has_open_quotes(token->str, pos))
			{
				adding_new_token(token, pos, ops[i]);
				token = token->next; //skips the operator token and avoids infinite loop
				break ;
			}
		}
		token = token->next;
	}
}

int		process_tokens(t_commands *command)
{
	/* struct stat	f; */

	if (has_unclosed_quotes(command->token))
		return (ERROR);
	if (!check_builtins(command) && !check_bins(command->token, command->envp))
	{
		printf("%s\n", CNF);
		return (0);
	}
	/* DO WE REALLY NEED THIS?
	if (lstat(token->str, &f) != -1)
	{
		if (f.st_mode & __S_IFDIR)
		{
			token = token->next;
			change_dir(token->str);
			return (1);
		}	
		if (f.st_mode & S_IXUSR)
			return(run_cmd("", token, envp));
	} */
	return (1);
}

void	parser(t_commands *commands)
{
	int	res;

	while (commands)
	{
		check_tokens(commands->token);
		res = process_tokens(commands);
		if (res != 1)
		{
			if (res == ERROR)
				printf("%s\n", EPROMPT);
		}
		commands = commands->next;
	}
}
