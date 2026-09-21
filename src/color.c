/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:50:28 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/19 23:42:24 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

static int	clamp(double n)
{
	if (n < 0.0)
		return (0);
	if (n > 255.0)
		return (255);
	return ((int)n);
}

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

t_color	add_colors(t_color a, t_color b)
{
	return ((t_color){
		clamp((double)(a.r + b.r)),
		clamp((double)(a.g + b.g)),
		clamp((double)(a.b + b.b))
	});
}

t_color	apply_light(t_color object, t_color light, double strength)
{
	t_color	result;

	result.r = clamp(object.r * (light.r / 255.0) * strength);
	result.g = clamp(object.g * (light.g / 255.0) * strength);
	result.b = clamp(object.b * (light.b / 255.0) * strength);
	return (result);
}
