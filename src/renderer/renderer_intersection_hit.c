/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_intersection_hit.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 13:22:34 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/15 09:46:05 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_intersection.h"
#include <math.h>

t_hit	make_hit(double t, t_vec3 point, t_vec3 surface_n, t_color color)
{
	t_hit	hit;

	if (!isfinite(t) || !isfinite(point.x) || !isfinite(point.y)
		|| !isfinite(point.z) || !isfinite(surface_n.x)
		|| !isfinite(surface_n.y) || !isfinite(surface_n.z))
		return (no_hit());
	surface_n = vec3_normal(surface_n);
	if (vec3_length_squared(surface_n) == 0.0)
		return (no_hit());
	hit.hit = 1;
	hit.t = t;
	hit.point = point;
	hit.normal = surface_n;
	hit.color = color;
	return (hit);
}

t_hit	no_hit(void)
{
	t_hit	hit;

	hit = (t_hit){0};
	return (hit);
}
