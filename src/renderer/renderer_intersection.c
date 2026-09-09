/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:51:03 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/09 15:46:05 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "renderer_intersection.h"

static void	update_closest(t_hit *closest, t_hit candidate)
{
	if (candidate.hit && (!closest->hit || candidate.t < closest->t))
		*closest = candidate;
}

t_hit	find_closest_intersection(t_scene *scene, t_ray ray)
{
	t_hit		closest;
	t_hit		candidate;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;

	closest = (t_hit){0};
	sphere = scene->spherell;
	while (sphere)
	{
		candidate = intersect_sphere(ray, sphere);
		update_closest(&closest, candidate);
		sphere = sphere->next;
	}
	plane = scene->planell;
	while (plane)
	{
		candidate = intersect_plane(ray, plane);
		update_closest(&closest, candidate);
		plane = plane->next;
	}
	cylinder = scene->cylinderll;
	while (cylinder)
	{
		candidate = intersect_cylinder(ray, cylinder);
		update_closest(&closest, candidate);
		cylinder = cylinder->next;
	}
	return (closest);
}

t_hit	make_hit(double t, t_vec3 point, t_vec3 normal, t_color color)
{
	t_hit	hit;

	hit.hit = 1;
	hit.t = t;
	hit.point = point;
	hit.normal = vec3_normalize(normal);
	hit.color = color;
	return (hit);
}

t_hit	no_hit(void)
{
	t_hit	hit;

	hit.hit = 0;
	return (hit);
}
