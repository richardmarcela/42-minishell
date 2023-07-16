/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:49:15 by riolivei          #+#    #+#             */
/*   Updated: 2023/07/16 22:47:18 by mrichard         ###   ########.fr       */
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

	if (isquote(command[(*pos) + 1]) && command[(*pos) + 2] != '$'
		&& command[(*pos) + 2] != '\0')
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

	printf("ENTROU ADD CHARS\n");
	printf("- expanding str: '%s'\n", expanding_str);
	temp = ft_substr(str, start, pos);
	printf("- temp: '%s'\n", temp);
	if (expanding_str && temp)
	{
		new_str = ft_strjoin(expanding_str, temp);
		if (ft_strcmp(expanding_str, "$"))
			free(expanding_str);
		free(temp);
		printf("-- expanding str: '%s'\n", expanding_str);
		printf("-- temp: '%s'\n", temp);
		printf("-- new str: '%s'\n", new_str);
		printf("SAIU ADD CHARS COM NEW STR\n");
		return (new_str);
	}
	printf("- expanding str: '%s'\n", expanding_str);
	printf("- temp: '%s'\n", temp);
	printf("SAIU ADD CHARS COM TEMP\n");
	return (temp);
}

char	*if_variable(char *new_str, t_commands *command, int *start, int *i)
{
	printf("ENTROU IF VARIABLE\n");
	printf("new str before: '%s'\n", new_str);

	new_str = process_variable(command->token->str, i, new_str, command->env);
	printf("- new str after: '%s'\n", new_str);

	(*start) = (*i);
	(*i)--;
/* 	if (!ft_strcmp(new_str, "$") && ft_strlen(new_str) > 1)
	{
		printf("-- new str: '%s'\n", new_str);
		free(new_str);
		printf("SAIU IF VARIABLE COM $\n");
		return ("$");
	}
	printf("- new str: '%s'\n", new_str); */
	printf("SAIU IF VARIABLE\n");
	return (new_str);
}

char	*if_quotes(char *new_str, t_commands *command, int *start, int *i)
{
	char	*temp;
	char	*handling;

	printf("ENTROU IF QUOTES\n");

	printf("- new str before: '%s'\n", new_str);
	temp = new_str;
	handling = quote_handler(command->token->str, i, (*i) + 1, command->env);
	new_str = ft_strjoin(temp, handling);
	free(temp);
	printf("- handling: '%s'\n", handling);
	if (handling && ft_strcmp(handling, "$"))
		free(handling);
	(*start) = (*i) + 1;
	printf("- new str after: '%s'\n", new_str);
	printf("SAIU IF QUOTES\n");

	return (new_str);
}
