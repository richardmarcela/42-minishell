/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:46:41 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/25 22:10:40 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_env *env, int flag)
{
	while (env)
	{
		if (flag)
			printf("declare -x ");
		printf("%s\n", env->str);
		env = env->next;
	}
	return (1);
}

char	*env_value(char *str, t_env *env)
{
	int		pos;
	char	*env_name;
	char	*value;

	value = NULL;
	while (env)
	{
		pos = search_ops_in_str(env->str, "=");
		env_name = ft_substr(env->str, 0, pos);
		if (!ft_strcmp(str, env_name))
		{
			value = ft_strtrim(ft_strchr(env->str, '='), "=");
			free(env_name);
			break ;
		}
		env = env->next;
		free(env_name);
	}
	return (value);
}
