/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:33:14 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/25 20:14:40 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	crazy(char *line)
{
	if (!ft_strcmp(line, "crazy"))
	{
		printf("\nCrazy? I was crazy once\n");
		printf("They locked me in a room, a rubber room\n");
		printf("A rubber room with rats, and rats make me crazy\n\n");
		return (1);
	}
	return (0);
}
