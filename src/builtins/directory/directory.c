/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:40:37 by mrichard          #+#    #+#             */
/*   Updated: 2023/05/04 20:55:16 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dir(char *dir)
{
	if (!dir)
		dir = getenv("HOME");
	if (chdir(dir))
	{
		printf("%s\n", UNKNOWN);
		return (0);
	}
	return (1);
}