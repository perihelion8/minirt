/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 13:35:00 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/19 23:42:01 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

int		color_isvalid(t_color color);
int		color_rgb_hex(int r, int g, int b);
t_color	add_colors(t_color a, t_color b);
t_color	apply_light(t_color object, t_color light, double strength);

#endif
