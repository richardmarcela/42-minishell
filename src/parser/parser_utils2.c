/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:49:15 by riolivei          #+#    #+#             */
/*   Updated: 2023/07/15 18:30:47 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_variable(char *str, int *pos)
{
	char	*variable;
	int		i;
	int		n;

	i = (*pos) + 1;
	n = 0;
	while (str[i] != '$' && str[i] != ASPAS
		&& str[i] != PLICAS && str[i] != ' ' && str[i])
	{
		n++;
		i++;
	}
	(*pos) = i - 1;
	variable = malloc(sizeof(char) * n + 1);
	variable[n] = '\0';
	i = -1;
	while (n--)
		variable[++i] = str[(*pos) - n];
	return (variable);
}

char	*search_variable(char *command, int *pos, t_env *env)
{
	char	*var_name;
	char	*value;

	if (isquote(command[(*pos) + 1]) && (command[(*pos) + 2] != '$'
		&& command[(*pos) + 2] != '\0'))
		value = NULL;
	else if (!ft_isalnum(command[(*pos) + 1]))
		value = "$";
	else
	{
		var_name = get_variable(command, pos);
		if (!ft_strcmp(var_name, "?"))
			value = ft_itoa(g_exit_status);
		else
			value = env_value(var_name, env);
		free(var_name);
	}
	(*pos) += 1;
	return (value);
}

char	*add_chars(char *expanding_str, char *str, int pos, int start)
{
	char	*new_str;
	char	*temp;

	temp = ft_substr(str, start, pos);
	if (expanding_str && temp)
	{
		new_str = ft_strjoin(expanding_str, temp);
		if (ft_strcmp(expanding_str, "$"))
			free(expanding_str);
		free(temp);
		return (new_str);
	}
	else
		return (temp);
}

char	*if_variable(char *new_str, t_commands *command, int *start, int *i)
{
	printf("ENTROU IF VARIABLE\n");
	printf("- NEW_STR BEFORE: %s\n", new_str);
	new_str = process_variable(command->token->str, i, new_str, command->env);
	printf("- NEW_STR AFTER: %s\n", new_str);
	(*start) = (*i);
	(*i)--;
	return (new_str);
}

char	*if_quotes(char *new_str, t_commands *command, int *start, int *i)
{
	char	*temp;
	char	*handling;
	
	printf("ENTROU IF QUOTES\n");
	printf("- NEW_STR BEFORE: %s\n", new_str);
	temp = new_str;
	handling = quote_handler(command->token->str, i, (*i) + 1, command->env);
	printf("- HANDLING: %s\n", handling);
	new_str = ft_strjoin(temp, handling);
	printf("- NEW_STR AFTER: %s\n", new_str);
	free(temp);
	if (handling && ft_strcmp(handling, "$"))
		free(handling);
	(*start) = (*i) + 1;
	return (new_str);
}
