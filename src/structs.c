/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:54:22 by mrichard          #+#    #+#             */
/*   Updated: 2023/03/18 21:26:56 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void    *init(t_command_line *command, char *line)
{
    int             i;
    
    i = -1;
    command->str = malloc(sizeof(char) * ft_strlen(line) + 1);
    command->str[ft_strlen(line)] = '\0';
    lexer(command);
    return (command->str);
} */

void    lexer(char *line)
{
    t_commands *commands;

    commands->array_commands = malloc(sizeof(t_command_line) * 1);
}