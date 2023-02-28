/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 03:12:59 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/28 21:51:46 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_command(char *command)
{
	int	len;
	int	res;

	len = ft_strlen(command) - 1;
	res = 1;
	if (command[0] == 34 && command[len] == 34)
	{
		res = 2;
		if (count(command, 34) % 2 != 0)
			res = 0;
	}
	else if (command[0] == 39 && command[len] == 39)
	{
		res = 3;
		if (count(command, 39) % 2 != 0)
			res = 0;
	}
	else if ((command[0] == 34 && command[len] != 34)
		|| (command[0] != 34 && command[len] == 34))
		return (0);
	else if ((command[0] == 39 && command[len] != 39)
		|| (command[0] != 39 && command[len] == 39))
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

void	print(char *command)
{
	int		method;
	char	*new_str;

	new_str = skip_echo(command);
	method = check_command(new_str);
	if (!method)
		printf("%s\n", EPROMPT);
	else if (method == 1)
		no_quotes(new_str);
	else if (method == 2)
		double_quotes(new_str);
	else
		single_quotes(new_str);
	free(new_str);
}
