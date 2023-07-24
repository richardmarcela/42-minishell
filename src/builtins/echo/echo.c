/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:46:24 by riolivei          #+#    #+#             */
/*   Updated: 2023/07/24 17:11:41 by mrichard         ###   ########.fr       */
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
		if (token->str)
			printf("%s", token->str);
		if (token->next)
			printf(" ");
		token = token->next;
	}
	if (flag)
		printf("\n");
	return (1);
}
