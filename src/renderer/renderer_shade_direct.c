/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_shade_direct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 23:44:11 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 12:40:47 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_shade.h"

t_color	direct_light(t_scene *scene, t_hit *hit, t_light *light)
{
	t_color	diffuse;
	t_vec3	light_direction;
	double	lambert;

	if (light->ratio <= 0.0)
		return ((t_color){0, 0, 0});
	light_direction = vec3_normal(vec3_subtract(light->pos, hit->point));
	lambert = vec3_dot(hit->normal, light_direction);
	if (lambert <= 0.0 || is_shadowed(scene, hit, light))
		return ((t_color){0, 0, 0});
	diffuse = apply_light(hit->color, light->color, light->ratio * lambert);
	return (add_colors(diffuse,
			specular_light(scene, hit, light, light_direction)));
}
