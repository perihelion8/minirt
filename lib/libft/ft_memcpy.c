/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:58:42 by abazzoun          #+#    #+#             */
/*   Updated: 2025/09/17 13:54:15 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*srcb;
	unsigned char		*dstb;

	srcb = (const unsigned char *) src;
	dstb = (unsigned char *) dst;
	while (n--)
		*dstb++ = *srcb++;
	return (dst);
}
