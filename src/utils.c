/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:38:25 by riolivei          #+#    #+#             */
/*   Updated: 2023/03/01 20:26:11 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*current_directory(void)
{
	char	*dir;

	dir = malloc(sizeof(char) * 200);
	return (getcwd(dir, 200));
}

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

int	ft_start_with(char *s1, char *s2)
{
	int	i;

	i = -1;
	while(s2[++i])
		if (s1[i] != s2[i])
			return (0);
	return (1);
}

void	exit_and_free(void)
{
	ft_free(global_env);
	printf("\n");
	exit(0);
}

void	ft_free(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = -1;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
	ptr = NULL;
}

