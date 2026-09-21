/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:51:03 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 12:42:44 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "renderer_intersection.h"

static double	intersect_shape(t_ray *ray, t_shape *shape)
{
	if (shape->type == PLANE)
		return (intersect_pl(ray, &shape->plane));
	if (shape->type == SPHERE)
		return (intersect_sp(ray, &shape->sphere));
	if (shape->type == CYLINDER)
		return (intersect_cy(ray, &shape->cylinder));
	if (shape->type == HYPERB)
		return (intersect_hb(ray, &shape->hyperboloid));
	return (-1.0);
}

static void	hit_shape(t_ray *ray, t_shape *shape, t_hit *closest)
{
	if (shape->type == PLANE)
		hit_pl(ray, &shape->plane, closest);
	else if (shape->type == SPHERE)
		hit_sp(ray, &shape->sphere, closest);
	else if (shape->type == CYLINDER)
		hit_cy(ray, &shape->cylinder, closest);
	else if (shape->type == HYPERB)
		hit_hb(ray, &shape->hyperboloid, closest);
	if (vec3_dot(closest->normal, ray->direction) > 0.0)
		closest->normal = vec3_scale(closest->normal, -1.0);
}

t_hit	find_closest_intersection(t_scene *scene, t_ray *ray)
{
	t_shape		*shape;
	t_hit		closest;
	double		t;
	size_t		i;

	closest = no_hit();
	closest.t = DBL_MAX;
	i = 0;
	shape = scene->shapea;
	while (i < scene->shapea_len)
	{
		t = intersect_shape(ray, shape++);
		if (t != -1.0 && t < closest.t)
		{
			closest.hit = 1;
			closest.t = t;
			closest.index = i;
		}
		++i;
	}
	if (!closest.hit)
		return (no_hit());
	hit_shape(ray, scene->shapea + closest.index, &closest);
	return (closest);
}

int	find_intersection(t_scene *scene, t_ray *ray, double max_distance)
{
	size_t	i;
	double	t;
	t_shape	*shape;

	shape = scene->shapea;
	i = 0;
	while (i < scene->shapea_len)
	{
		t = intersect_shape(ray, shape++);
		if (t != -1.0 && t < max_distance)
			return (1);
		++i;
	}
	return (0);
}
