/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:22:39 by mrichard          #+#    #+#             */
/*   Updated: 2023/03/02 18:54:18 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	setenv()
{

} */

char	*get_env_var(char *var)
{
	int	i;
	char	*tmp;

	i = -1;
	while (global_env[++i])
	{
		tmp = ft_strjoinch(var, '=');
		if (ft_start_with(global_env[i], tmp))
		{
			free(tmp);
			return (ft_strchr(global_env[i], '=') + 1);
		}
		free(tmp);
	}
	return (NULL);
}