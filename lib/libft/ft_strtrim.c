/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:35:30 by a                 #+#    #+#             */
/*   Updated: 2025/09/12 20:00:42 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
