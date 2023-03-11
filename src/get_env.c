/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:20:52 by riolivei          #+#    #+#             */
/*   Updated: 2023/03/11 18:46:04 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_env_value(char *line)
{
	int	i;
	int j;
	int len;
	char *value;
	
	i = 0;
	while(line[i] != '=')
		i++;
	len = ft_strlen(line) - i;
	value = malloc(len + 1 * sizeof(char));
	value[len] = '\0';
	j = -1;
	while(++j < len)
		value[j] = line[++i];
	return	(value);
}

char	*get_env_name(char *line)
{
	int	i;
	int	j;
	char *name;
	
	i = 0;
	while(line[i] != '=')
		i++;
	name = malloc(i + 1 * sizeof(char));
	name[i]= '\0';
	j = -1;
	while(++j < i)
		name[j] = line[j];
	return (name);
}

int	has_spaces(char *line)
{
	int	i;

	i = -1;
	while(line[++i])
		if (line[i] == ' ')
			return (1);
	return (0);
}