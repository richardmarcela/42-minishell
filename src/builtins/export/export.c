/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 22:09:34 by mrichard          #+#    #+#             */
/*   Updated: 2023/05/04 22:47:33 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static int  envp_size(char **envp)
{
    int count;

    count = 0;
    while (envp[count])
        count++;
    return (count);
} */

int    export(t_commands *command)
{
    int     size;
   
    printf("%s\n", command->token->str);
    
    return(1);
}