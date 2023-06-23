/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:40:37 by mrichard          #+#    #+#             */
/*   Updated: 2023/06/23 18:14:32 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dir(t_tokens *token, t_env *env)
{
	char	*dir;

	dir = NULL;
	if (!token->next || !ft_strcmp(token->next->str, "~"))
		dir = env_value("HOME", env);
	else
		dir = token->next->str;
	if (chdir(dir))
	{
		g_exit_status = 1;
		printf("%s\n", UNKNOWN);
	}
	//free(dir);
	return (1);
}
