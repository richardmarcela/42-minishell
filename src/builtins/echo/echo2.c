/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:49:15 by riolivei          #+#    #+#             */
/*   Updated: 2023/06/01 17:13:00 by mrichard         ###   ########.fr       */
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

void	search_variable(char *command, int *pos, t_env *env)
{
	int		i;
	char	*value;

	i = (*pos);
	if (command[i + 1] == ' ' || command[i + 1] == '\0')
		printf("%c", command[i]);
	else
	{
		value = env_value(get_variable(command, &i), env);
		if (value)
			printf("%s", value);
	}
	(*pos) = i + 1;
}

void	change_flag(bool *flag)
{
	if (!*flag)
		*flag = true;
	else
		*flag = false;
}

//MAIS DE 4 PARAMETROS
void	quote_handler(char *str, int *pos,
bool *unclosed_squotes, bool *unclosed_quotes, t_env *env)
{
	if (str[*pos] == PLICAS)
	{
		(*pos)++;
		change_flag(unclosed_squotes);
		while (str[*pos] && str[*pos] != PLICAS)
			printf("%c", str[(*pos)++]);
		change_flag(unclosed_squotes);
	}
	else
	{
		(*pos)++;
		change_flag(unclosed_quotes);
		while (str[*pos] && str[*pos] != ASPAS)
		{
			if (!(*unclosed_squotes))
			{
				if (str[*pos] == '$')
					search_variable(str, pos, env);
				else
					printf("%c", str[(*pos)++]);
			}
		}
		change_flag(unclosed_quotes);
	}
}

void	process_argument(char *str, t_env *env)
{
	int		i;
	bool	unclosed_quotes;
	bool	unclosed_squotes;

	unclosed_quotes = false;
	unclosed_squotes = false;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && !unclosed_squotes)
			search_variable(str, &i, env);
		if (isquote(str[i]))
			quote_handler(str, &i, &unclosed_squotes, &unclosed_quotes, env);
		else
			printf("%c", str[i]);
	}
}
