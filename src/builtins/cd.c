/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:40:37 by mrichard          #+#    #+#             */
/*   Updated: 2023/06/01 19:53:31 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dir(t_tokens *token, t_env *env)
{
	char	*dir;

	dir = NULL;
	if (!token->next)
		dir = env_value("HOME", env);
	else
		dir = token->next->str;
	if (chdir(dir))
	{
		g_exit_status = 1;
		printf("%s\n", UNKNOWN);
		return (1);
	}
	return (0);
}
