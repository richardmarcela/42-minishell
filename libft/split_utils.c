/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:20:36 by mrichard          #+#    #+#             */
/*   Updated: 2023/06/29 16:25:56 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	*attr_values(void)
{
	bool	*variables;

	variables = malloc(sizeof(bool) * 4);
	variables[0] = false;
	variables[1] = false;
	variables[2] = false;
	variables[3] = false;
	return (variables);
}

int	process_res(bool *variables)
{
	int	res;

	res = 0;
	if (variables[0] || variables[1])
		res = 1;
	free(variables);
	return (res);
}
