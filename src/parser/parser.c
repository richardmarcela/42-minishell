/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:26:06 by riolivei          #+#    #+#             */
/*   Updated: 2023/04/08 21:41:52 by riolivei         ###   ########.fr       */
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

int unclosed_quotes(t_commands *commands)
{
    while (commands)
    {
        while(commands->token)
        {
            if (has_unclosed_quotes(commands->token->str))
                return (1);
            commands->token = commands->token->next;
        }
        commands = commands->next;
    }
    return (0);
}

void    parser(t_commands *commands, t_env	*env)
{
    struct stat	f;
    (void)env;
    
    if (unclosed_quotes(commands))
    {
        //ah e tal cheio de merda
        //tem unclosed quotes num dos tokens
        readline(EPROMPT);
        return ;
    }
    while (commands)
    {
        if (commands->token->type == SETTING && lstsize_tokens(commands->token) == 1)
        {
            //se tiver a dar set a uma variavel
            //faz merdas e avanca nos tokens
            commands->token = commands->token->next;
        }
        if (check_builtins(commands->token, env) /* || check_bins(commands->token, env) */)
            return ;
        if (lstat(commands->token->str, &f) != -1)
        {
            if (f.st_mode & __S_IFDIR)
            {
                commands->token = commands->token->next;
                /* change_dir(commands->token->str); */
                return ;
            }	
            /* if (f.st_mode & S_IXUSR)
                return(run_cmd(ft_strdup(commands->token->str), commands)); */
        }
        commands = commands->next;
    }
}
