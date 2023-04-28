/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:46:24 by riolivei          #+#    #+#             */
/*   Updated: 2023/04/27 20:41:54 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count(char *command, int n)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (command[++i])
		if (command[i] == n)
			count++;
	return (count);
}

int	is_right_flag(char *str)
{
	if (!ft_strcmp(ft_strtrim(str, "\""), "-n") || !ft_strcmp(ft_strtrim(str, "'"), "-n"))
		return (1);
	return (0);
}

int	has_unclosed_quotes(t_tokens *token)
{
	while (token)
	{
		//printf("token = %s\n", token->str);
		if (count(token->str, PLICAS) % 2 != 0 || count(token->str, ASPAS) % 2 != 0)
			return (1);
		token = token->next;
	}
	return (0);
}

int	print(t_tokens *token)
{
	bool	flag;
	
	flag = true;
	if (token == NULL) //quando echo n tem args nem flags
		return(printf("\n"));
	if(token->type == OPTION && is_right_flag(token->str))
	{
		flag = false;
		token = token->next;
	}
	while (token)
	{
		process_argument(token->str);
		if (token->next)
			printf(" ");
		token = token->next;
	}
	if (flag)
		printf("\n");
	/* ft_free(line); */
	return (1);
}