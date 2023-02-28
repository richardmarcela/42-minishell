/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:01:11 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/28 05:23:16 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//identifica o comando e o que deve fazer a seguir
int	processing(char **line)
{
	char	*pwd;

	if (!ft_strcmp(line[0], "cd"))
	{
		change_dir(line[1]);
		return (1);
	}
	if (!ft_strcmp(line[0], "pwd"))
	{
		pwd = current_directory();
		printf("%s\n", pwd);
		free(pwd);
		return (1);
	}
	if (!ft_strcmp(line[0], "ls"))
	{
		content_dir(line[1]);
		return (1);
	}
	if (!ft_strcmp(line[0], "echo"))
	{
		print(line);
		return (1);
	}
	return (0);
}
