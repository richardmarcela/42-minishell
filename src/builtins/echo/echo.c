/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:46:24 by riolivei          #+#    #+#             */
/*   Updated: 2023/07/06 17:59:18 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count(char *command, int n)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (command[++i])
		if (command[i] == n)
			count++;
	return (count);
}

int	is_right_flag(char *str)
{
	char	*squote_trim;
	char	*dquote_trim;
	
	squote_trim = ft_strtrim(str, "'");
	dquote_trim = ft_strtrim(str, "\"");
	if (!ft_strcmp(dquote_trim, "-n")
		|| !ft_strcmp(squote_trim, "-n"))
	{
		free(squote_trim);
		free(dquote_trim);
		return (1);
	}
	free(squote_trim);
	free(dquote_trim);
	return (0);
}

int	print(t_tokens *token, t_env *env)
{
	bool	flag;

	flag = true;
	if (token == NULL)
		return (printf("\n"));
	if (token->type == OPTION && is_right_flag(token->str))
	{
		flag = false;
		token = token->next;
	}
	while (token)
	{
		printf("STR: %s\n", token->str);
		process_argument(token->str, env);
		if (token->next)
			printf(" ");
		token = token->next;
	}
	if (flag)
		printf("\n");
	return (1);
}
