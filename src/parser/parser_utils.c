/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:30:04 by mrichard          #+#    #+#             */
/*   Updated: 2023/06/10 20:26:11 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_content(char *str, char *op, int flag)
{
	char	*string;
	int		size;

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
	t_tokens	*op_token;

	token->str = ft_substr(token->str, 0, pos);
	token->type = token_type(token->str);
	op_token = lstnew_token(op, token_type(op));
	if (!search_content(original_str, op, 1))
		op_token->next = token->next;
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
