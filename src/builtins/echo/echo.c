/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:46:24 by riolivei          #+#    #+#             */
/*   Updated: 2023/04/20 22:14:29 by riolivei         ###   ########.fr       */
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

/* int	check_command(char *command)
{
	int	len;
	int	res;

	len = ft_strlen(command) - 1;
	res = 1;
	if (command[0] == ASPAS && command[len] == ASPAS)
	{
		res = 2;
		if (count(command, ASPAS) % 2 != 0)
			res = 0;
	}
	else if (command[0] == PLICAS && command[len] == PLICAS)
	{
		res = 3;
		if (count(command, PLICAS) % 2 != 0)
			res = 0;
	}
	else if ((command[0] == ASPAS && command[len] != ASPAS)
		|| (command[0] != ASPAS && command[len] == ASPAS))
		return (0);
	else if ((command[0] == PLICAS && command[len] != PLICAS)
		|| (command[0] != PLICAS && command[len] == PLICAS))
		return (0);
	return (res);
} */

int	is_right_flag(char *str)
{
	if (!ft_strcmp(ft_strtrim(str, "\""), "-n") || !ft_strcmp(ft_strtrim(str, "'"), "-n"))
		return (1);
	return (0);
}

int	has_unclosed_quotes(char *str)
{
	if (count(str, PLICAS) % 2 != 0 || count(str, ASPAS) % 2 != 0)
		return (1);
	return (0);
}

int	print(t_tokens *token)
{
	/* int		method; */
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
		/* method = check_command(token->str); */
		/* if (method == 1)
			no_quotes(token->str);
		else if (method == 2)
			double_quotes(token->str);
		else
			single_quotes(token->str);
		if (token->next)
			printf(" "); */
		token = token->next;
	}
	if (flag)
		printf("\n");
	/* ft_free(line); */
	return (1);
}