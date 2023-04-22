/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:43:10 by riolivei          #+#    #+#             */
/*   Updated: 2023/04/21 18:14:47 by riolivei         ###   ########.fr       */
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
		while (s[i] == ' ' && !has_open_quotes(s, i) && c == ' ')
		{
			i++;
			flag = 0;
		}
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
		if (s[i] == c && !has_open_quotes(s, i))
			break ;
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

	if (!s)
		return (NULL);
	i = 0;
	j = -1;
	words = count_words(s, c);
	str = (char **)malloc((words + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (++j < words)
	{
		while (s[i] == c)
			i++;
		str[j] = ft_substr(s, i, count_letters(s, c, i));
		if (!str)
			return (NULL);
		i += count_letters(s, c, i);
	}
	str[j] = 0;
	return (str);
}