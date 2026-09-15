/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_intersection_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:51:03 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/15 09:45:27 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "renderer_intersection.h"

static void	update_closest(t_hit *closest, t_hit candidate)
{
	if (candidate.hit && (!closest->hit || candidate.t < closest->t))
		*closest = candidate;
}

static t_hit	intersect_shape(t_ray ray, t_shape *shape)
{
	if (shape->type == PLANE)
		return (intersect_pl(ray, &shape->plane));
	if (shape->type == SPHERE)
		return (intersect_sp(ray, &shape->sphere));
	if (shape->type == CYLINDER)
		return (intersect_cy(ray, &shape->cylinder));
	if (shape->type == HYPERBOLOID)
		return (intersect_hp(ray, &shape->hyperboloid));
	return (no_hit());
}

t_hit	find_closest_intersection(t_scene *scene, t_ray ray)
{
	t_hit		closest;
	t_hit		candidate;
	t_shape		*shape;

	closest = (t_hit){0};
	shape = scene->shapell;
	while (shape)
	{
		candidate = intersect_shape(ray, shape);
		update_closest(&closest, candidate);
		shape = (t_shape *)shape->node.next;
	}
	if (closest.hit && vec3_dot(closest.normal, ray.direction) > 0.0)
		closest.normal = vec3_scale(closest.normal, -1.0);
	return (closest);
}

t_hit	find_intersection(t_scene *scene, t_ray ray)
{
	t_shape	*shape;
	t_hit	hit;

	shape = scene->shapell;
	while (shape)
	{
		hit = intersect_shape(ray, shape);
		if (hit.hit)
			return (hit);
		shape = (t_shape *)shape->node.next;
	}
	return (no_hit());
}
