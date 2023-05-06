/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 20:23:02 by mrichard          #+#    #+#             */
/*   Updated: 2023/05/06 21:07:15 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void delete(t_env *env, int i)
{
    
} */

int unset_env(t_commands *command)
{
    (void)command;
    /* int i;
    t_env *current;

    i = 0;
    current = command->env;
    while (command->env)
    {
        if (!ft_strcmp(command->token->str, current->str))
            delete(command->env, i);
        i++;
        current = current->next;
    }*/
    return (1);
} 
