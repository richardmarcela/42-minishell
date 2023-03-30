/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:26:06 by riolivei          #+#    #+#             */
/*   Updated: 2023/03/30 22:50:44 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    parser(t_commands *commands, char **envp)
{
    t_env *env;
    
    while (commands)
    {
        while (commands->token)
        {
            printf("%u\n", commands->token->type);
            commands->token = commands->token->next;
        }
        commands = commands->next;
    }
    env = init_env(envp);
}

static int  red_count(char *str, int c)
{
    int i;
    int count;

    i = -1;
    count = 0;
    while (str[++i])
    {
        if (str[i] == c)
            count++;
    }
    return (count);
}

TokenType   which_red(char *str)
{
    // OUT NUNCA VEM ANTES DO IN
    if (red_count(str, '>') == 1 && red_count(str, '<') == 1)
        return (IN_OUT);
    if (red_count(str, '>') == 1) // >
        return (RED_OUT);
    if (red_count(str, '<') == 1) // <
        return (RED_IN);
    if (red_count(str, '>') == 2 && red_count(str, '<') == 0) // >>
        return (APPEND_OUT);
    if (red_count(str, '<') == 2 && red_count(str, '>') == 0) // <<
        return (APPEND_IN);
    return (ERRO);
}
