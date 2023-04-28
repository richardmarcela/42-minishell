/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 22:46:03 by riolivei          #+#    #+#             */
/*   Updated: 2023/04/27 17:09:49 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_tokens *token, char **envp)
{
	//char	*pwd;
	(void)envp;
    
	if (!ft_strcmp(token->str, "echo"))
		return (print(token->next));
	return (0);
	/*else if (!ft_strcmp(token->str, "cd"))
    {
        token = token->next;
		return (change_dir(token->str));
    }
	else if (!ft_strcmp(token->str, "pwd"))
	{
		pwd = current_directory();
		printf("%s\n", pwd);
		free(pwd);
		return (1);
	}
	else if (!ft_strcmp(line[0], "unset"))
		unsetenv();
	else if (!ft_strcmp(line[0], "export"))
		export();
	[TIREI DAQUI O ENV PQ E UM BINARIO]
	return (0);*/
}