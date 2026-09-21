/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_shade.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:52:32 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 05:11:19 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_shade.h"
#include <math.h>

int	is_shadowed(t_scene *scene, t_hit *hit, t_light *light)
{
	t_ray	shadow_ray;
	t_vec3	to_light;
	double	light_distance;

	shadow_ray.origin = vec3_add(hit->point,
			vec3_scale(hit->normal, RENDER_SHADOW_BIAS));
	to_light = vec3_subtract(light->pos, shadow_ray.origin);
	light_distance = vec3_length(to_light);
	if (light_distance == 0.0)
		return (0);
	shadow_ray.direction = vec3_scale(to_light, 1.0 / light_distance);
	return (find_intersection(scene, &shadow_ray,
			light_distance - RENDER_SHADOW_BIAS));
}

t_color	shade_hit(t_scene *scene, t_hit *hit)
{
	t_color	result;
	size_t	i;

	result = apply_light(hit->color, scene->ambient.color,
			scene->ambient.ratio);
	result = add_colors(result, direct_light(scene, hit, &scene->light));
	i = 0;
	while (i < scene->spotlighta_len)
	{
		result = add_colors(result,
				spotlight(scene, hit, &scene->spotlighta[i]));
		++i;
	}
	return (result);
}
