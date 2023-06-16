/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands_list_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:16:31 by mrichard          #+#    #+#             */
/*   Updated: 2023/06/16 20:32:37 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_pipe_splitted(char **pipe_splitted)
{
	/* char	*trimmed;

	trimmed = ft_strtrim(pipe_splitted[0], " ");
	printf("trimmed: '%s'\n", trimmed);
	if (!pipe_splitted[0])
		return (0);
	if (!ft_strlen(trimmed))
	{
		free(trimmed);
		return (0);
	} */
	printf("string: '%s'\n", pipe_splitted[0]);
	if (pipe_splitted == NULL)
	{
		free(pipe_splitted);
		return (0);
	}
	if (has_empty_pipe(pipe_splitted))
	{
		g_exit_status = 1;
		printf("%s\n", EPARSE);
		/* free(trimmed); */
		return (0);
	}
	/* free(trimmed); */
	return (1);
}
