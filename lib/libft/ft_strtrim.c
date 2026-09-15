/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:35:30 by a                 #+#    #+#             */
/*   Updated: 2026/09/10 16:21:57 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(const char *s, const char *set)
{
	char	*trimmed;
	size_t	len;
	size_t	i;

	if (s == NULL || set == NULL)
		return (NULL);
	while (*s && ft_strchr(set, *s))
		s++;
	len = ft_strlen(s);
	i = 0;
	while (i < len && ft_strchr(set, s[len - 1 - i]))
		i++;
	len -= i;
	trimmed = (char *)malloc(sizeof(*trimmed) * (len + 1));
	if (trimmed == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		trimmed[i] = s[i];
		i++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}
