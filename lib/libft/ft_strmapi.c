/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:10:55 by a                 #+#    #+#             */
/*   Updated: 2025/06/17 16:31:23 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(t_uint, char))
{
	t_uint	i;
	char	*mapped;

	if (s == NULL || f == NULL)
		return (NULL);
	mapped = (char *)malloc(sizeof(*mapped) * (ft_strlen(s) + 1));
	if (mapped == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		mapped[i] = f(i, s[i]);
		i++;
	}
	mapped[i] = '\0';
	return (mapped);
}
