/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:29:00 by mrichard          #+#    #+#             */
/*   Updated: 2023/04/20 21:41:40 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/minishell.h"
#define ASPAS 34
#define PLICAS 39

/* int	process_words_in_quotes(char const *str, int *quoted, int *flag, char c)
{
	int	res;

	res = 0;
	if (!*quoted)
	{
		*quoted = 1;
		if (*(str - 1) == c && *(str - 1))
		{
			*flag = 1;
			res++;
		}
	}
	else
		*quoted = 0;
	return (res);
}

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
			words += process_words_in_quotes(s, &quoted, &flag, c);
		if (!quoted)
		{
			if (*s != c && flag == 0)
			{
				words++;
				flag = 1;
			}
			else if (*s == c)
				flag = 0;
		}
		s++;
	}
	if (c == ' ' && quoted)
		words++;
	return (words);
} 


static int skip_quoted_content(const char *str, int *pos)
{
	(*pos)++;
	while (str[*pos] && !isquote(str[*pos]))
		(*pos)++;
	return (*pos + 1);
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
	int		word_count;
	char	**str;

	printf("CHAR = '%c'\n", c);
	printf("STRING = %s\n", s);
	i = 0;
	j = -1;
	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	printf("WORDS = %d\n", word_count);
	str = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (++j < word_count)
	{
		while (s[i] == c)
			i++;
		str[j] = ft_substr(s, i, count_letters(s, c, i));
		if (!str)
			return (NULL);
		i += count_letters(s, c, i);
	}
	str[j] = 0;
	printf("--------------------------------------------------\n");
	return (str);
}
*/
