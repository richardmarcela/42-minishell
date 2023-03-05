/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 21:43:27 by riolivei          #+#    #+#             */
/*   Updated: 2023/03/05 16:21:48 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//recebe a posição do '$' e guarda tudo atè ao próximo '$' ou final da string
//num char* e procura nas variáveis de ambiente
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

void	search_variable(char *command, int *pos)
{
	int		i;
	char	*env;

	i = (*pos);
	if (command[i + 1] == ' ' || command[i + 1] == '\0')
		printf("%c", command[i]);
	else
	{
		env = getenv(get_variable(command, &i));
		if (env)
			printf("%s", env);
	}
	(*pos) = i + 1;
}

void	no_quotes(char *command)
{
	int	i;

	i = -1;
	while (command[++i])
	{
		while (command[i] == '$')
			search_variable(command, &i);
		while (command[i] == ' ' && command[i + 1] == ' ')
			i++;
		if (command[i] != ASPAS) //ignorar aspas(")
			printf("%c", command[i]);
	}
}

void	double_quotes(char *command)
{
	int	i;

	i = -1;
	while (command[++i])
	{
		while (command[i] == '$')
			search_variable(command, &i);
		if (command[i] != ASPAS) //ignorar aspas(")
			printf("%c", command[i]);
	}
}

void	single_quotes(char *command)
{
	int	i;

	i = -1;
	while (command[++i])
	{
		if (command[i] != PLICAS) //ignorar plicas(')
			printf("%c", command[i]);
	}
}
