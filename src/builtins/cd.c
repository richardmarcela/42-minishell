/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:40:37 by mrichard          #+#    #+#             */
/*   Updated: 2023/05/20 18:32:01 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dir(char *dir, t_env *env)
{
	if (!dir)
		dir = env_value("HOME", env);
	if (chdir(dir))
	{
		g_exit_status = 1;
		printf("EXIT STATUS NO SUCH FILE OR DIR: %d\n", g_exit_status);
		printf("%s\n", UNKNOWN);
		return (0);
	}
	return (1);
}