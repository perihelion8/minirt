/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_transforms.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 17:32:51 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/11 17:59:06 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder_transforms.h"
#include "renderer_ray.h"
#include "vector.h"

t_ray	cy_raytorel(t_ray ray, const t_cylinder *cy)
{
	t_ray	rel_ray;
	t_vec3	rel_ray_o;

	rel_ray_o = vec3_subtract(ray.origin, cy->pos);
	rel_ray.origin.x = vec3_dot(rel_ray_o, cy->right);
	rel_ray.origin.y = vec3_dot(rel_ray_o, cy->up);
	rel_ray.origin.z = vec3_dot(rel_ray_o, cy->axis);
	rel_ray.direction.x = vec3_dot(ray.direction, cy->right);
	rel_ray.direction.y = vec3_dot(ray.direction, cy->up);
	rel_ray.direction.z = vec3_dot(ray.direction, cy->axis);
	return (rel_ray);
}

t_vec3	cy_pointtoabs(const t_cylinder *cy, t_vec3 rel)
{
	t_vec3	point;

	point = vec3_add(cy->pos, vec3_scale(cy->right, rel.x));
	point = vec3_add(point, vec3_scale(cy->up, rel.y));
	point = vec3_add(point, vec3_scale(cy->axis, rel.z));
	return (point);
}
