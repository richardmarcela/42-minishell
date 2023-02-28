/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 03:12:59 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/28 05:29:31 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//recebe a posição do '$' e guarda tudo atè ao próximo '$' ou final da string
//num char* e procura nas variáveis de ambiente
char	*get_variable(char *str, int pos)
{
	char	*variable;
	int		i;
	int		n;

	i = pos + 1;
	n = 0;
	while (str[i] != '$' && str[i] != '"' && str[i])
	{
		n++;
		i++;
	}
	variable = malloc(sizeof(char) * n + 1);
	variable[n] = '\0';
	i = -1;
	while (n--)
	{
		pos++;
		variable[++i] = str[(pos)];
	}
	return (getenv(variable));
}

void	string(char *str)
{
	int		i;
	char	*env;
	bool	flag;

	i = -1;
	flag = true;
	if (str[0] == 39 && str[ft_strlen(str)-1] == 39)
		flag = false;
	while (str[++i])
	{
		//variáveis de ambiente não são processadas entre plicas (')
		if (flag)
		{	
			if (str[i] == '$')
			{
				env = get_variable(str, i);
				if (env)
					printf("%s", env);
				i++;
				while (str[i] != '$' && str[i]) //atualiza o índice
					i++;
				i--; //recua uma posição para voltar a verificar se tem '$'
				continue ;
			}
			if (str[i] != 34 && str[i] != 39) //ignorar aspas(") e plicas(')
				printf("%c", str[i]);
			continue ;
		}
		if (str[i] != 34 && str[i] != 39) //ignorar aspas(") e plicas(')
			printf("%c", str[i]);
	}
}

void	print(char **str)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		string(str[i]);
		if (str[i + 1]) //evita um espaço a mais na última palavra
			printf(" ");
	}
	printf("\n");
}
