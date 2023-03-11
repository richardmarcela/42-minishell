/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 03:12:59 by riolivei          #+#    #+#             */
/*   Updated: 2023/03/11 20:58:01 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_error(void)
{
	while (1)
		readline((EPROMPT));
}

int	check_command(char *command)
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
}

int	print(char **line)
{
	int		method;
	int		i;
	bool	flag;

	flag = true;
	i = 0;
	if(!ft_strcmp(ft_strtrim(line[1] , "\""), "-n"))
	{
		i++;
		flag = false;
	}
	while (line[++i])
	{
		method = check_command(line[i]);
		if (method == 1)
			no_quotes(line[i]);
		else if (method == 2)
			double_quotes(line[i]);
		else
			single_quotes(line[i]);
		if (line[i + 1])
			printf(" ");
	}
	if (flag)
		printf("\n");
	ft_free(line);
	return (1);
}
