/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:05:54 by a                 #+#    #+#             */
/*   Updated: 2025/06/17 16:37:53 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	digits_count(int n)
{
	size_t	count;

	if (n == -2147483648)
		return (12);
	count = 0;
	if (n < 0)
	{
		count++;
		n = -1 * n;
	}
	while (1)
	{
		count++;
		n /= 10;
		if (n <= 0)
			break ;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*number;
	size_t	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = digits_count(n);
	number = (char *)malloc(sizeof(*number) * (len + 1));
	if (number == NULL)
		return (NULL);
	number[len] = '\0';
	if (n < 0)
	{
		number[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		number[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (number);
}
