/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:21:28 by a                 #+#    #+#             */
/*   Updated: 2025/09/17 13:56:32 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**split_create(const char *s, char c)
{
	char	**split;
	size_t	size;
	int		in_word;

	if (s == NULL)
		return (NULL);
	size = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (in_word == 0)
		{
			size++;
			in_word = 1;
		}
		s++;
	}
	split = (char **)malloc(sizeof(*split) * (size + 1));
	if (split == NULL)
		return (NULL);
	return (split);
}

static char	**split_destroy_and_return_null(char **split, size_t i)
{
	while (i--)
		free(split[i]);
	free(split);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**split;
	size_t	i;
	size_t	len;

	split = split_create(s, c);
	if (split == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		if (len > 0)
		{
			split[i] = ft_substr(s, 0, len);
			if (split[i] == NULL)
				return (split_destroy_and_return_null(split, i));
			s += len - 1;
			i++;
		}
		s++;
	}
	split[i] = NULL;
	return (split);
}
