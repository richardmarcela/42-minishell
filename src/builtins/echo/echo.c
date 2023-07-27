/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:46:24 by riolivei          #+#    #+#             */
/*   Updated: 2023/07/27 13:55:23 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_all(t_tokens *token)
{
	t_tokens	previous;

	previous = *token;
	while (token)
	{
		if (token->str && !is_redirect(token->str,
				token->was_quoted) && !is_redirect(previous.str,
				previous.was_quoted))
			printf("%s", token->str);
		if (token->next && token->next->str)
			printf(" ");
		previous = *token;
		token = token->next;
	}
}

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
	print_all(token);
	if (flag)
		printf("\n");
	return (1);
}
