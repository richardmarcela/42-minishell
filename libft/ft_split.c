/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:29:00 by mrichard          #+#    #+#             */
/*   Updated: 2023/04/08 22:39:33 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/minishell.h"
#define ASPAS 34
#define PLICAS 39

static int	count_words(char const *s, char c)
{
	int	words;
	int	flag;
	int	quoted;

	words = 0;
	flag = 0;
	quoted = 0;
	while (*s)
	{
		if (isquote(*s))
		{
			if (!quoted)
			{
				//o if abaixo serve para tratar unclosed quotes iniciais (ex: "a)
				// unclosed quotes finais (ex: a") funcionam sem problema
				quoted = 1;
				if (*(s-1) == c)
				{
					words++;
					flag = 1;
				}
			}
			else
				quoted = 0;
		}
		if (!quoted)
		{
			if (*s != c && flag == 0)
			{
				flag = 1;
				words++;
			}
			else if (*s == c)
				flag = 0;
		}
		s++;
	}
	return (words);
}

static int skip_quoted_content(const char *str, int *pos)
{
	int count;

	count = 1;
	(*pos)++;
	while (str[*pos] && !isquote(str[*pos]))
	{
		count++;
		(*pos)++;
	}
	return (count + 1);
}

static int	count_letters(char const *s, char c, int i)
{
	int	size;
	int pos;
	
	pos = i;
	size = 0;
	while (s[pos] && s[pos] != c)
	{
		if (isquote(s[pos]))
			size += skip_quoted_content(s, &pos);
		else
			size++;
		pos++;
	}
	return (size);
}

char	**ft_split(char *s, char c)
{
	int		i;
	int		j;
	int		word;
	char	**str;

	i = 0;
	j = -1;
	if (!s)
		return (NULL);
	word = count_words(s, c);
	str = (char **)malloc((word + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (++j < word)
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
