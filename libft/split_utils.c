/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:20:36 by mrichard          #+#    #+#             */
/*   Updated: 2023/06/01 21:41:38 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	*attr_values(void)
{
	bool	*variables;

	variables = malloc(sizeof(bool) * 5);
	variables[4] = '\0';
	variables[0] = false;
	variables[1] = false;
	variables[2] = false;
	variables[3] = false;
	return (variables);
}
