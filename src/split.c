/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 01:14:28 by riolivei          #+#    #+#             */
/*   Updated: 2023/02/28 05:30:36 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_words(char const *s, char c)
{
	int	words;
	int	flag;

	words = 0;
	flag = 0;
	while (*s)
	{
		if (*s != c && flag == 0)
		{
			flag = 1;
			words++;
		}
		else if (*s == c)
			flag = 0;
		s++;
	}
	return (words);
}

static int	count_letters(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != c && s[i])
	{
		size++;
		i++;
	}
	return (size);
}

char	*get_line(const char *str, int pos, int n)
{
	char	*string;
	int		i;

	string = malloc(sizeof(char) * n + 1);
	string[n] = '\0';
	i = 0;
	while (n--)
	{
		string[i] = str[pos + i];
		i++;
	}
	return (string);
}

char	**ft_split(char const *s, char c)
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
		str[j] = get_line(s, i, count_letters(s, c, i));
		if (!str)
			return (NULL);
		i += count_letters(s, c, i);
	}
	str[j] = 0;
	return (str);
}
