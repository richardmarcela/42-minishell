/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 22:09:34 by mrichard          #+#    #+#             */
/*   Updated: 2023/05/05 19:09:32 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    export(t_commands *command)
{
    t_env *new;
    
    if (ft_strchr(command->token->str, '='))
    {
        new = lstnew_env(command->token->str);
        lstadd_back_env(&command->env, new);
    }
    return (1);
}