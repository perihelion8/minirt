/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_shade.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:52:32 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/12 15:42:22 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_shade.h"

static int	clamp(double n)
{
	if (n < 0.0)
		return (0);
	if (n > 255.0)
		return (255);
	return ((int)n);
}

static t_vec3	apply_light(t_color object, t_color light, double strength)
{
	t_vec3	result;

	result.x = object.r * (light.r / 255.0) * strength;
	result.y = object.g * (light.g / 255.0) * strength;
	result.z = object.b * (light.b / 255.0) * strength;
	return (result);
}

static int	is_shadowed(t_scene *scene, const t_hit *hit, t_light *light)
{
	t_ray	shadow_ray;
	t_hit	blocker;
	t_vec3	to_light;
	double	light_distance;

	shadow_ray.origin = vec3_add(hit->point,
			vec3_scale(hit->normal, RENDER_SHADOW_BIAS));
	to_light = vec3_subtract(light->pos, shadow_ray.origin);
	light_distance = vec3_length(to_light);
	shadow_ray.direction = vec3_normal(to_light);
	blocker = find_closest_intersection(scene, shadow_ray);
	return (blocker.hit && blocker.t < light_distance - RENDER_SHADOW_BIAS);
}

t_color	shade_hit(t_scene *scene, const t_hit *hit)
{
	t_vec3	result;
	t_light	*light;
	t_vec3	light_direction;
	double	lambert;

	result = apply_light(hit->color, scene->ambient.color,
			scene->ambient.ratio);
	light = scene->lightll;
	while (light)
	{
		light_direction = vec3_normal(vec3_subtract(light->pos, hit->point));
		lambert = vec3_dot(hit->normal, light_direction);
		if (lambert > 0.0 && !is_shadowed(scene, hit, light))
			result = vec3_add(result, apply_light(hit->color, light->color,
						light->ratio * lambert));
		light = (t_light *)light->node.next;
	}
	return ((t_color){clamp(result.x), clamp(result.y), clamp(result.z)});
}
