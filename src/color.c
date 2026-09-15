/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:50:28 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/10 07:35:12 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int	color_isvalid(t_color color)
{
	if (color.r < 0 || color.r > 255)
		return (0);
	if (color.g < 0 || color.g > 255)
		return (0);
	if (color.b < 0 || color.b > 255)
		return (0);
	return (1);
}

int	color_rgb_hex(const int r, const int g, const int b)
{
	return ((r << 16) | (g << 8) | b);
}
