/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:49:49 by mrichard          #+#    #+#             */
/*   Updated: 2023/05/05 19:58:44 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **fill_env_matrix(t_env *env)
{
	int     i;
	int     size;
	char    **envp;

	i = -1;
	size = env_len(env) + 1;
	envp = malloc(sizeof(char *) * size);
	envp[size - 1] = NULL;
	while (++i < size - 1)
	{
		envp[i] = env->str;
		env = env->next;
	}
	return (envp);
}