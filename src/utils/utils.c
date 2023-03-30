/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:51:42 by riolivei          #+#    #+#             */
/*   Updated: 2023/03/30 18:14:25 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int isquote(int c)
{
	if (c == ASPAS || c == PLICAS)
		return 1;
	return 0;
}

/* void    ft_free(t_command_line *command)
{
    free(command->str);
} */
