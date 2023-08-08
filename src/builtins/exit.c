/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:57:40 by mrichard          #+#    #+#             */
/*   Updated: 2023/08/08 15:57:17 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long	ft_atoll(const char *str)
{
	long long	res;
	int			signal;
	int			i;

	res = 0;
	signal = 1;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i += 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signal = -1;
		i += 1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i += 1;
	}
	return (res * signal);
}

static int	streq(char *str1, char *str2)
{
	size_t	i;

	if ((str1 && !str2) || (!str1 && str2))
		return (0);
	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i += 1;
	}
	return (1);
}

static int	fits_in_longlong(char *str)
{
	long long	out;
	int			c;

	if (ft_strlen(str) > 20)
		return (0);
	if (streq("-9223372036854775808", str))
		return (1);
	out = 0;
	if (*str == '-' || *str == '+')
		str += 1;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		c = *str - '0';
		if (out > (LLONG_MAX - c) / 10)
			return (0);
		out = out * 10 + c;
		str += 1;
	}
	return (1);
}

static int	is_digit_signal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (0);
		i += 1;
	}
	return (1);
}

int	exit_terminal(t_commands *command)
{
	int		size;

	size = lstsize_tokens(command->token, 0);
	if (size <= 2)
	{
		if (size == 2)
		{
			if (is_digit_signal(command->token->next->str)
				&& fits_in_longlong(command->token->next->str))
				g_exit_status = ft_atoll(command->token->next->str);
			else
			{
				g_exit_status = 2;
				printf("exit\n%s\n", NAR);
				exit(g_exit_status);
			}
		}
		else
			g_exit_status = EXIT_SUCCESS;
		free_structs(command, 1);
		printf("exit\n");
		exit(g_exit_status);
	}
	g_exit_status = EXIT_FAILURE;
	return (printf("%s\n", TMA));
}
