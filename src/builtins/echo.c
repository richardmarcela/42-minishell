/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 03:12:59 by riolivei          #+#    #+#             */
/*   Updated: 2023/03/01 00:18:58 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*skip_echo(char *command)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(command);
	i = -1;
	while (command[++i] == ' ')
		len--;
	len -= 4;
	i += 4;
	while (command[++i] == ' ')
		len--;
	str = malloc(sizeof(char) * len);
	str[len] = '\0';
	j = -1;
	while (command[i])
	{
		str[++j] = command[i];
		i++;
	}
	return (str);
}

char	*skip_newline(char *command)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(command);
	len -= 2;
	i = 1;
	while (command[++i] == ' ')
		len--;
	str = malloc(sizeof(char) * len);
	str[len] = '\0';
	j = -1;
	while (command[i])
	{
		str[++j] = command[i];
		i++;
	}
	return (str);
}

void	print(char *command)
{
	int		method;
	bool	flag;
	char	*new_str;

	flag = true;
	new_str = skip_echo(command);
	if(new_str[0] == '-' && new_str[1] == 'n')
	{
		new_str = skip_newline(new_str);
		flag = false;
	}
	method = check_command(new_str);
	if (!method)
		printf("%s", EPROMPT);
	else if (method == 1)
		no_quotes(new_str);
	else if (method == 2)
		double_quotes(new_str);
	else
		single_quotes(new_str);
	if (flag)
		printf("\n");
	free(new_str);
}
