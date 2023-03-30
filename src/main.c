/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:53:02 by mrichard          #+#    #+#             */
/*   Updated: 2023/03/30 22:48:59 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//LINE E A LINHA INTEIRA

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char  *line;

    while (1)
    {
        line = readline(PROMPT);
        pipe_split(line, envp);
        add_history(line);
        free(line);
    }
    return (0);
}