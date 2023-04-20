/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:26:06 by riolivei          #+#    #+#             */
/*   Updated: 2023/04/20 22:15:05 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int lstsize_tokens(t_tokens *token)
{
	int	count;

	count = 0;
	while (token)
	{
		count++;
		token = token->next;
	}
	return (count);
}

int	process_tokens(t_tokens *token, t_env *env)
{
	struct stat	f;

	while (token)
	{
		printf("%s\n", token->str);
		token = token->next;
	}
	while (token)
	{
		if (has_unclosed_quotes(token->str))
			return (ERROR);
		if (token->type == SETTING && lstsize_tokens(token) == 1)
		{
			//se tiver a dar set a uma variavel
			//faz merdas e avanca nos tokens
			token = token->next;
		}
		if (check_builtins(token, env)  /* || check_bins(token, env) */)
			break ;
		if (lstat(token->str, &f) != -1)
		{
			if (f.st_mode & __S_IFDIR)
			{
				token = token->next;
				/* change_dir(token->str); */
				return (1);
			}	
			/* if (f.st_mode & S_IXUSR)
				return(run_cmd(ft_strdup(token->str), commands)); */
		}
		token = token->next;
	}
	return (1);
}

void	parser(t_commands *commands, t_env	*env)
{
	(void)env;
	
	while (commands)
	{
		if (process_tokens(commands->token, env) == ERROR)
		{
			readline(EPROMPT);
			break ;
		}
		commands = commands->next;
	}
}
