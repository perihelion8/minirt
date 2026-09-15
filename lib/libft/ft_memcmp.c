/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:49:03 by a                 #+#    #+#             */
/*   Updated: 2026/09/10 16:10:32 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *m1, const void *m2, size_t n)
{
	const unsigned char	*m1b;
	const unsigned char	*m2b;
	size_t				i;

	if (n == 0)
		return (0);
	m1b = (const unsigned char *) m1;
	m2b = (const unsigned char *) m2;
	i = 0;
	while (m1b[i] == m2b[i] && i + 1 < n)
		i++;
	return (m1b[i] - m2b[i]);
}
