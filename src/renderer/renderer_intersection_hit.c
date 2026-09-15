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

t_hit	make_hit(double t, t_vec3 point, t_vec3 surface_n, t_color color)
{
	t_hit	hit;

	hit.hit = 1;
	hit.t = t;
	hit.point = point;
	hit.normal = vec3_normal(surface_n);
	hit.color = color;
	return (hit);
}

t_hit	no_hit(void)
{
	t_hit	hit;

	hit = (t_hit){0};
	return (hit);
}
