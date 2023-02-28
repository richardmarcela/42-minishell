/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:01:11 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/28 18:10:31 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//identifica o comando e o que deve fazer a seguir
int	processing(char **line)
{
	char	*pwd;

	if (!ft_strcmp(line[0], "cd"))
		change_dir(line[1]);
	else if (!ft_strcmp(line[0], "pwd"))
	{
		pwd = current_directory();
		printf("%s\n", pwd);
		free(pwd);
	}
	else if (!ft_strcmp(line[0], "ls") || !ft_strcmp(line[0], "/bin/ls"))
		content_dir(line[1]);
	else
		return (0);
	return (1);
}
