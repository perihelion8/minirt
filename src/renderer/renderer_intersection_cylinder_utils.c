/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_intersection_cylinder_utils.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:51:38 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/09 17:46:03 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "renderer_intersection.h"

t_component_of_ray	to_cylinder_space(t_ray ray, const t_cylinder *cy)
{
	t_component_of_ray	component_of_ray;
	t_vec3				relative_origin;

	relative_origin = vec3_subtract(ray.origin, cy->pos);
	component_of_ray.origin_right = vec3_dot(relative_origin, cy->right);
	component_of_ray.origin_up = vec3_dot(relative_origin, cy->up);
	component_of_ray.origin_forward = vec3_dot(relative_origin,
			cy->axis);
	component_of_ray.direction_right = vec3_dot(ray.direction, cy->right);
	component_of_ray.direction_up = vec3_dot(ray.direction, cy->up);
	component_of_ray.direction_forward = vec3_dot(ray.direction,
			cy->axis);
	return (component_of_ray);
}

t_vec3	to_world_point(const t_cylinder *cy, double x, double y, double z)
{
	t_vec3	point;

	point = vec3_add(cy->pos, vec3_scale(cy->right, x));
	point = vec3_add(point, vec3_scale(cy->up, y));
	return (vec3_add(point, vec3_scale(cy->axis, z)));
}
