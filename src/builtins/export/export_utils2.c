/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:54:56 by mrichard          #+#    #+#             */
/*   Updated: 2023/06/29 18:09:08 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* char	*first_if()
{
	
} */

char	*second_if(char *result, char *input, int *i, t_env *env)
{
	char	*new_res;
	char	*variable;

	variable = env_search_variable(input, i, env);
	new_res = ft_strjoin(result, variable);
	(*i)--;
	free(variable);
	free(result);
	return (new_res);
}

char	*third_if(char *result, char *input, int *i)
{
	int		start;
	char	*str;
	char	*new_res;

	start = (*i);
	while (input[(*i)] && !isquote(input[(*i)]) && input[(*i)] != '$')
			(*i)++;
	str = ft_substr(input, start, (*i));
	new_res = ft_strjoin(result, str);
	free(str);
	free(result);
	return (new_res);
}

char	*attr_value_result(char *result, char *input, int *i, t_env *env)
{
	char	*new_res;
	char	*quote;
	bool	*quotes;

	quotes = attr_values_quotes();
	new_res = result;
	if (isquote(input[(*i)]))
	{
		quote = env_quote_handler(input, i, &quotes, env);
		new_res = ft_strjoin(result, quote);
		free(quote);
		free(result);
	}
	else if (input[(*i)] == '$' && !quotes[1])
		new_res = second_if(result, input, i, env);
	else
		new_res = third_if(result, input, i);
	free(quotes);
	return (new_res);
}
