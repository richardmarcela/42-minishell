/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 00:51:45 by marcela           #+#    #+#             */
/*   Updated: 2023/05/18 16:20:12 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* #include <stdio.h> */

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*new_str;
	size_t	len_s1;
	size_t	len_s2;

	i = 0;
	j = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new_str = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (new_str == NULL)
		return (NULL);
	while (j < len_s1)
		new_str[i++] = s1[j++];
	j = 0;
	while (j < len_s2)
		new_str[i++] = s2[j++];
	new_str[i] = '\0';
	return (new_str);
}
