/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:43:10 by riolivei          #+#    #+#             */
/*   Updated: 2023/05/27 18:32:00 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define ASPAS 34
#define PLICAS 39

static int	skip_quoted_content(char *s, int *i, int *flag)
{
	if (!(*flag))
	{
		if (s[(*i) + 1])
			(*i)++;
		while (s[*i] && !isquote(s[*i]))
			(*i)++;
		(*flag) = 1;
		return (1);
	}
	return (0);
}

int	has_open_quotes(char *str, int pos)
{
	int		i;
	int		counts;
	int		countd;
	bool	squote;
	bool	dquote;

	i = 0;
	counts = 0;
	countd = 0;
	squote = false;
	dquote = false;
	while (str[i] && i < pos)
	{
		if (isquote(str[i]))
		{
			if (str[i] == ASPAS && !squote)
			{
				change_flag(&dquote);
				countd++;
			}
			else if (str[i] == PLICAS && !dquote)
			{
				change_flag(&squote);
				counts++;
			}
		}
		i++;
	}
	if (counts % 2 != 0 || countd % 2 != 0)
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
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == ' ' && !has_open_quotes(s, i) && c == ' ')
		{
			i++;
			flag = 0;
		}
		if (s[i] && isquote(s[i]))
			words += skip_quoted_content(s, &i, &flag);
		if (s[i] && s[i] != c && flag == 0 && !isquote(s[i]))
		{
			flag = 1;
			words++;
		}
		else if (s[i] && s[i] == c && !has_open_quotes(s, i))
			flag = 0;
		i++;
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
