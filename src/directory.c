/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 00:51:30 by riolivei          #+#    #+#             */
/*   Updated: 2023/03/04 19:49:01 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define HIDE_HIDDEN entry->d_name[0] != '.'

int	change_dir(char *dir)
{
	if (!dir)
		dir = getenv("HOME");
	if (chdir(dir))
	{
		printf("%s\n", UNKNOWN);
		return (0);
	}
	return (1);
}


/*void	content_dir(char *flag)
{
	 DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
	{
		printf("\n");
		return ;
	}
	while ((entry = readdir(dir))) 
	{
		if (!flag)
		{
			if (entry->d_name && HIDE_HIDDEN)
				printf("%s ", entry->d_name);
		}
		else if (flag[1] && flag[1] == 'a')
		{
			if (entry->d_name)
				printf("%s ", entry->d_name);	
		}
	}
	printf("\n");	
	if (closedir(dir) == -1)
	{
		printf("\n");
		return ;
	} */


