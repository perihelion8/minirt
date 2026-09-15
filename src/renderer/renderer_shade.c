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

static t_color	add_colors(t_color a, t_color b)
{
	return ((t_color){
		clamp((double)(a.r + b.r)),
		clamp((double)(a.g + b.g)),
		clamp((double)(a.b + b.b))
	});
}

static t_color	apply_light(t_color object, t_color light, double strength)
{
	t_color	result;

	result.r = clamp(object.r * (light.r / 255.0) * strength);
	result.g = clamp(object.g * (light.g / 255.0) * strength);
	result.b = clamp(object.b * (light.b / 255.0) * strength);
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
	t_color	ambient;
	t_color	diffuse;
	t_vec3	light_direction;
	double	lambert;

	ambient = apply_light(hit->color, scene->ambient.color,
			scene->ambient.ratio);
	light_direction = vec3_subtract(scene->light.pos, hit->point);
	light_direction = vec3_normal(light_direction);
	lambert = vec3_dot(hit->normal, light_direction);
	if (lambert <= 0.0 || is_shadowed(scene, hit, &scene->light))
		return (ambient);
	diffuse = apply_light(hit->color, scene->light.color,
			scene->light.ratio * lambert);
	return (add_colors(ambient, diffuse));
}
