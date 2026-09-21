/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 17:32:51 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/19 01:53:34 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_utils.h"
#include "renderer_ray.h"

t_ray	cy_ray_to_rel(t_ray *ray, const t_cylinder *cy)
{
	t_ray	rel_ray;
	t_vec3	rel_ray_origin;

	rel_ray_origin = vec3_subtract(ray->origin, cy->pos);
	rel_ray.origin.x = vec3_dot(rel_ray_origin, cy->right);
	rel_ray.origin.y = vec3_dot(rel_ray_origin, cy->up);
	rel_ray.origin.z = vec3_dot(rel_ray_origin, cy->axis);
	rel_ray.direction.x = vec3_dot(ray->direction, cy->right);
	rel_ray.direction.y = vec3_dot(ray->direction, cy->up);
	rel_ray.direction.z = vec3_dot(ray->direction, cy->axis);
	return (rel_ray);
}

t_vec3	cy_point_to_abs(const t_cylinder *cy, t_vec3 rel_point)
{
	t_vec3	abs_point;

	abs_point = vec3_add(cy->pos, vec3_scale(cy->right, rel_point.x));
	abs_point = vec3_add(abs_point, vec3_scale(cy->up, rel_point.y));
	abs_point = vec3_add(abs_point, vec3_scale(cy->axis, rel_point.z));
	return (abs_point);
}

t_vec3	hb_point_to_abs(const t_hyperboloid *hb, t_vec3 rel_point)
{
	t_vec3	abs_point;

	abs_point = vec3_add(hb->pos, vec3_scale(hb->right, rel_point.x));
	abs_point = vec3_add(abs_point, vec3_scale(hb->up, rel_point.y));
	abs_point = vec3_add(abs_point, vec3_scale(hb->axis, rel_point.z));
	return (abs_point);
}

t_ray	hb_ray_to_rel(t_ray *ray, const t_hyperboloid *hb)
{
	t_ray	rel_ray;
	t_vec3	rel_ray_origin;

	rel_ray_origin = vec3_subtract(ray->origin, hb->pos);
	rel_ray.origin.x = vec3_dot(rel_ray_origin, hb->right);
	rel_ray.origin.y = vec3_dot(rel_ray_origin, hb->up);
	rel_ray.origin.z = vec3_dot(rel_ray_origin, hb->axis);
	rel_ray.direction.x = vec3_dot(ray->direction, hb->right);
	rel_ray.direction.y = vec3_dot(ray->direction, hb->up);
	rel_ray.direction.z = vec3_dot(ray->direction, hb->axis);
	return (rel_ray);
}
