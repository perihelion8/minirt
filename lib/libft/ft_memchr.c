/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:32:26 by a                 #+#    #+#             */
/*   Updated: 2025/09/17 13:48:34 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *m, int c, size_t n)
{
	const unsigned char	*mb;
	size_t				i;

	mb = m;
	i = 0;
	while (i < n)
	{
		if (mb[i] == c)
			return ((void *)(mb + i));
		i++;
	}
	return (NULL);
}
