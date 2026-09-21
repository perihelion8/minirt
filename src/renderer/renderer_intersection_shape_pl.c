/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_intersection_shape_pl.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:51:44 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/18 23:57:49 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_intersection.h"
#include "math/floating_point.h"

double	intersect_pl(t_ray *ray, t_plane *pl)
{
	double	t;
	t_vec3	rel_ray;
	double	ray_dot_normal;

	ray_dot_normal = vec3_dot(ray->direction, pl->normal);
	if (approximately_zero(ray_dot_normal))
		return (-1.0);
	rel_ray = vec3_subtract(pl->pos, ray->origin);
	t = vec3_dot(rel_ray, pl->normal) / ray_dot_normal;
	if (is_positive(t))
		return (t);
	return (-1.0);
}

void	hit_pl(t_ray *ray, t_plane *pl, t_hit *hit)
{
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
	hit->normal = pl->normal;
	hit->color = pl->color;
}
