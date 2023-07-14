/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:46:24 by riolivei          #+#    #+#             */
/*   Updated: 2023/07/13 21:56:19 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print(t_tokens *token)
{
	bool	flag;

	flag = true;
	if (token == NULL)
		return (printf("\n"));
	if (token->type == OPTION && !ft_strcmp(token->str, "-n"))
	{
		flag = false;
		token = token->next;
	}
	while (token)
	{
		printf("%s", token->str);
		if (token->next)
			printf(" ");
		token = token->next;
	}
	if (flag)
		printf("\n");
	return (1);
}
