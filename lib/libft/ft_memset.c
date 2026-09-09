/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:36:31 by abazzoun          #+#    #+#             */
/*   Updated: 2025/09/17 13:56:11 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *m, int c, size_t n)
{
	unsigned char	*mb;

	mb = m;
	while (n--)
		*mb++ = (unsigned char)c;
	return (m);
}
