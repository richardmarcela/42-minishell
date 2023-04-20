/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:43:10 by riolivei          #+#    #+#             */
/*   Updated: 2023/04/20 22:53:15 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/minishell.h"
#define ASPAS 34
#define PLICAS 39

static int	skip_quoted_content(char *s, int *i, int flag)
{
	if (!flag)
	{
		(*i)++;
		if (!s[*i])
			return (0);
		while (s[*i] && !isquote(s[*i]))
			(*i)++;
		return (1);
	}
	return (0);
}

static int	has_open_quotes(char *str, int pos)
{
	if (count(ft_substr(str, 0, pos), ASPAS) % 2 != 0 || count(ft_substr(str, 0, pos), PLICAS) % 2 != 0)
		return (1);
	return (0);
}

static int	count_words(char *s, char c)
{
	int	words;
	int	flag;
	int	i;

	words = 0;
	flag = 0;
	i = -1;
	while (s[++i])
	{
		if (isquote(s[i]))
			words += skip_quoted_content(s, &i, flag);
		if (s[i] != c && flag == 0 && !isquote(s[i]) && s[i])
		{
			flag = 1;
			words++;
		}
		else if (s[i] == c && !has_open_quotes(s, i))
			flag = 0;
	}
	return (words);
}

static int	count_letters(char *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i])
	{
		if (s[i] != c)
			size++;
		else if (!has_open_quotes(s, i))
		size++;
		i++;
	}
	return (size);
}

char	**ft_split(char *s, char c)
{
	int		i;
	int		j;
	int		words;
	char	**str;

	printf("CHAR = '%c'\n", c);
	printf("STRING = %s\n", s);
	if (!s)
		return (NULL);
	i = 0;
	j = -1;
	words = count_words(s, c);
	printf("WORDS = %d\n", words);
	str = (char **)malloc((words + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (++j < words)
	{
		str[j] = ft_substr(s, i, count_letters(s, c, i));
		printf("WORD [%d] = %s\n", j+1, str[j]);
		if (!str)
			return (NULL);
		i += count_letters(s, c, i);
	}
	str[j] = 0;
	printf("--------------------------------------------------\n");
	return (str);
}