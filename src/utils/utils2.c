/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 20:22:55 by mrichard          #+#    #+#             */
/*   Updated: 2023/07/20 19:54:05 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_ops(void)
{
	char	**ops;

	ops = (char **)malloc(sizeof(char *) * 5);
	ops[0] = ">";
	ops[1] = "<";
	ops[2] = ">>";
	ops[3] = "<<";
	ops[4] = 0;
	return (ops);
}

char	*env_str(char *env)
{
	int		i;
	int		size;
	char	*str;

	size = ft_strlen(env);
	str = (char *)malloc(sizeof(char) * (size + 1));
	str[size] = '\0';
	i = -1;
	while (++i < size)
		str[i] = env[i];
	return (str);
}

char	**fill_env_matrix(t_env *env)
{
	int		i;
	int		size;
	char	**envp;
	t_env	*node;

	node = env;
	size = env_len(node);
	envp = (char **)malloc(sizeof(char *) * (size + 1));
	envp[size] = 0;
	i = -1;
	while (++i < size)
	{
		envp[i] = env_str(node->str);
		if (node->next)
			node = node->next;
	}
	return (envp);
}

char	*arg_str(char *arg)
{
	int		i;
	int		size;
	char	*str;

	size = ft_strlen(arg);
	str = (char *)malloc(sizeof(char) * (size + 1));
	str[size] = '\0';
	i = -1;
	while (++i < size)
		str[i] = arg[i];
	return (str);
}

char	**fill_args(t_tokens *token)
{
	int			i;
	int			size;
	char		**args;
	t_tokens	previous;

	previous = *token;
	size = lstsize_tokens(token, 1);
	args = (char **)malloc(sizeof(char *) * (size + 1));
	args[size] = 0;
	i = 0;
	while (i < size)
	{
		if (!is_redirect(token->str) && !is_redirect(previous.str))
		{
			args[i] = arg_str(token->str);
			i++;
		}
		previous = *token;
		token = token->next;
	}
	return (args);
}
