/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:30:04 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/14 20:49:16 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_content(char *str, char *op, int flag)
{
	char	*string;
	int		size;

	printf("ENTROU SEARCH\n");
	printf("- ORIGINAL: %s\n", str);
	printf("- OPERATOR: %s\n", op);
	printf("- FLAG: %d\n", flag);
	if (!flag)
	{
		if (str[0] != op[0])
			return (1);
		return (0);
	}
	else
	{
		string = ft_strchr(str, op[0]);
		size = ft_strlen(op);
		if (string[size] && string[size] != op[0])
			return (1);
		return (0);
	}
}

void	handle_content_before(t_tokens *token, int pos,
	char *op, char *original_str)
{
	char		*str;
	t_tokens	*op_token;

	printf("--- TOKEN: %s\n", token->str);
	printf("--- POS: %d\n", pos);
	printf("--- OPERATOR: %s\n", op);
	printf("--- ORIGINAL: %s\n", original_str);
	printf("*** !!!EU ESTOU AQUI!!!\n");
	str = ft_strdup(token->str);
	token->str = ft_substr(str, 0, pos);
	free(str);
	printf("--- TOKEN CHANGED: %s\n", token->str);
	token->type = token_type(token->str);
	op_token = lstnew_token(op, token_type(op));
	printf("--- NEW OP TOKEN: %s\n", op_token->str);
	if (!search_content(original_str, op, 1))
	{
		printf("--- ENTROU IF\n");
		op_token->next = token->next;
	}
	token->next = op_token;
}

t_tokens	*handle_content_after(char *original_str, int pos,
	char *op, t_tokens *token)
{
	char		*new_str;

	new_str = ft_substr(original_str, pos + ft_strlen(op),
			ft_strlen(original_str) - ft_strlen(op)
			- ft_strlen(token->str));
	return (lstnew_token(new_str, token_type(new_str)));
}

char	*quote_handler(char *str, int *pos, int start, t_env *env)
{
	char	*new_str;

	(*pos)++;
	new_str = NULL;
	if (str[(*pos) - 1] == PLICAS)
	{
		while (str[*pos] && str[*pos] != PLICAS)
			(*pos)++;
		new_str = add_chars(new_str, str, ((*pos) - start), start);
	}
	else
	{
		while (str[*pos] && str[*pos] != ASPAS)
		{
			while (str[*pos] != '$' && str[*pos] && str[*pos] != ASPAS)
				(*pos)++;
			if (str[(*pos) - 1] != ASPAS)
				new_str = add_chars(new_str, str, ((*pos) - start), start);
			if (str[*pos] == '$')
			{
				new_str = process_variable(str, pos, new_str, env);
				start = *pos;
			}
		}
	}
	return (new_str);
}

char	*process_variable(char *str, int *i, char *expanding, t_env *env)
{
	char	*new_str;
	char	*temp;

	temp = search_variable(str, i, env);
	if (expanding)
	{
		new_str = ft_strjoin(expanding, temp);
		free(expanding);
		if (temp && ft_strcmp(temp, "$"))
			free(temp);
		return (new_str);
	}
	else
		return (temp);
}
