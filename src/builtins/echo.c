/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 03:12:59 by riolivei          #+#    #+#             */
/*   Updated: 2023/03/04 20:11:27 by mrichard         ###   ########.fr       */
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

/* char	*skip_echo(char *command)
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
} */

/* char	*skip_newline(char *command)
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
} */

int	print(char **line)
{
	int		method;
	int		i;
	bool	flag;

	flag = true;
	i = 0;
	while (line[++i])
	{
		method = check_command(line[i]);
		if (!method)
		{
			printf("%s", EPROMPT);
			free(line[i]);
			return (0);
		}
	}
	i = 0;
	if(!ft_strcmp(ft_strtrim(line[1] , "\""), "-n"))
	{
		i++;
		flag = false;
	}
	while (line[++i])
	{
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
