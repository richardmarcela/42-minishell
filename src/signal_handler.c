/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:03:41 by mrichard          #+#    #+#             */
/*   Updated: 2023/03/11 16:25:37 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    proc_signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        printf("\n");
        signal(SIGINT, proc_signal_handler);
    }
}