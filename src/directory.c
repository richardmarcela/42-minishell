/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 00:51:30 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/28 05:26:50 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_dir(char *dir)
{
	if (!dir)
		dir = getenv("HOME");
	if (chdir(dir))
		printf("%s\n", UNKNOWN);
}

void	content_dir(char *content)
{
	struct dirent	*ptr;

	if (!content)
		content = current_directory();
	if (opendir(content))
	{
		ptr = readdir(opendir(content));
		/* while(ptr)
		{ */
			printf("%s", ptr->d_name);
			ptr++;
		/* } */
		closedir(opendir(content));
		printf("\n");
		return ;
		/* printf("%s\n", UNKNOWN); */
	}
}
