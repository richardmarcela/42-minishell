/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:08:50 by mrichard          #+#    #+#             */
/*   Updated: 2023/05/05 20:10:44 by mrichard         ###   ########.fr       */
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