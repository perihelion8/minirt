/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_intersection_plane.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:51:44 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/09 17:22:36 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_intersection.h"
#include "math/floating_point.h"

t_hit	intersect_plane(t_ray ray, const t_plane *pl)
{
	t_vec3	cam_to_plane;
	t_vec3	point;
	double	ray_dot_normal;
	double	t;

	ray_dot_normal = vec3_dot(ray.direction, pl->normal);
	if (approximately_zero(ray_dot_normal))
		return (no_hit());
	cam_to_plane = vec3_subtract(pl->pos, ray.origin);
	t = vec3_dot(cam_to_plane, pl->normal) / ray_dot_normal;
	if (!is_positive(t))
		return (no_hit());
	point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
	return (make_hit(t, point, pl->normal, pl->color));
}
