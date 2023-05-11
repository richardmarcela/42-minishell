/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 20:23:02 by mrichard          #+#    #+#             */
/*   Updated: 2023/05/11 16:24:51 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    free_env_var(t_env *env)
{
    free(env->str);
    free(env);
}

int unset_env(t_commands *command)
{
    t_env   *prev;
    t_env   *curr;

    // Caso a variável a ser removida seja a primeira da lista
    if (!ft_strcmp(command->token->str, command->env->str))
    {
        curr = command->env;
        command->env = curr->next;
        free_env_var(curr);
        return (0);
    }
    prev = command->env;
    curr = prev->next;
    while (curr)
    {
        if (!ft_strcmp(command->token->str, curr->str))
        {
            prev->next = curr->next;
            free_env_var(curr);
            return (0);
        }
        prev = curr;
        curr = prev->next;
    }
    return (1);
}
