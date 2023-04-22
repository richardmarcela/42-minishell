/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 22:46:03 by riolivei          #+#    #+#             */
/*   Updated: 2023/04/22 16:58:54 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_tokens *token, t_env *env)
{
	char	*pwd;
	(void)env;
    
	if (!ft_strcmp(token->str, "echo"))
			return (print(token->next));
	else if (!ft_strcmp(token->str, "cd"))
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
	else if (!ft_strcmp(line[0], "env"))
		print_env();
	return (0);
}