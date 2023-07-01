/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 22:09:34 by mrichard          #+#    #+#             */
/*   Updated: 2023/06/29 18:19:17 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*env_get_variable(char *str, int *pos)
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

char	*env_search_variable(char *command, int *pos, t_env *env)
{
	int		i;
	char	*variable;
	char	*value;

	i = (*pos);
	variable = env_get_variable(command, &i);
	value = env_value(variable, env);
	free(variable);
	(*pos) = i + 1;
	if (value)
		return (value);
	free(value);
	return (NULL);
}

static void	env_change_flag(bool *flag)
{
	if (!*flag)
		*flag = true;
	else
		*flag = false;
}

//MAIS DE 25 LINHAS
char	*env_quote_handler(char *str, int *pos, bool **quotes, t_env *env)
{
	char	*new_str;
	int		start;

	new_str = NULL;
	(*pos)++;
	if (str[(*pos) - 1] == PLICAS)
	{
		start = (*pos);
		env_change_flag(quotes[1]);
		while (str[*pos] && str[*pos] != PLICAS)
			(*pos)++;
		new_str = ft_substr(str, start, (*pos) - start);
		env_change_flag(quotes[1]);
	}
	else
	{
		env_change_flag(quotes[0]);
		while (str[*pos] && str[*pos] != ASPAS)
		{
			if (str[*pos] == '$')
				new_str = ft_strjoin(new_str,
						env_search_variable(str, pos, env));
			else
				new_str = ft_strjoin(new_str, ft_substr(str, (*pos)++, 1));
		}
		env_change_flag(quotes[0]);
	}
	return (new_str);
}

char	*process_env_variable(char *input, t_env *env)
{
	int		i;
	char	*result;

	i = 0;
	while (input[i] && !isquote(input[i]) && input[i] != '$')
		i++;
	result = ft_substr(input, 0, i);
	while (input[i])
	{
		result = attr_value_result(result, input, &i, env);
		i++;
	}
	return (result);
}

/* char	*process_env_variable(char *input, t_env *env)
{
	int		i;
	int		start;
	bool	unclosed_quotes;
	bool	unclosed_squotes;
	char	*result;

	i = 0;
	unclosed_quotes = false;
	unclosed_squotes = false;
	while (input[i] && !isquote(input[i]) && input[i] != '$')
		i++;
	result = ft_substr(input, 0, i);
	while (input[i])
	{
		if (isquote(input[i]))
			result = ft_strjoin(result,
					env_quote_handler(input, &i, &unclosed_squotes,
						&unclosed_quotes, env));
		else if (input[i] == '$' && !unclosed_squotes)
		{
			result = ft_strjoin(result, env_search_variable(input, &i, env));
			i--;
		}
		else
		{
			start = i;
			while (input[i] && !isquote(input[i]) && input[i] != '$')
				i++;
			result = ft_strjoin(result, ft_substr(input, start, i));
		}
		i++;
	}
	return (result);
} */