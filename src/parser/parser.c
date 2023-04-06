/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:26:06 by riolivei          #+#    #+#             */
/*   Updated: 2023/04/06 22:58:56 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static int	setting_env(t_commands *commands)
{
	int		i;
	int		res;
    t_commands *current;
	t_list	*linked = NULL;

    if (lstsize_commands(commands) > 1)
        return (0);
    current = commands;
	res = 0;
    while (current)
    {
	    i = -1;
        while (current->token->str[++i])
            if (current->token->str[i] == '=')
                res = 1;
        if (res)
		ft_lstadd_back(&linked, ft_lstnew(get_env_name(current->token->str), get_env_value(current->token->str)));
        current = current->next;
    }
	
	
	return (res);
} */

void    parser(t_commands *commands, t_env	*env)
{
    struct stat	f;
    (void)env;
    
    while (commands)
    {
        while (commands->token)
        {
            /* if (setting_env(commands))
                return (1); */
            if (check_builtins(commands->token, env) || check_bins(commands->token))
                return ;
            if (lstat(commands->token->str, &f) != -1)
            {
                if (f.st_mode & __S_IFDIR)
                {
                    commands->token = commands->token->next;
                    change_dir(commands->token->str);
                    return ;
                }	
                /* if (f.st_mode & S_IXUSR)
                    return(run_cmd(ft_strdup(commands->token->str), commands)); */
            }
        }
        commands = commands->next;
    }
}
