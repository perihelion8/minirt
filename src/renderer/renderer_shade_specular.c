/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_shade_specular.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 22:35:13 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 12:28:05 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_shade.h"
#include <math.h>

static t_vec3	reflect(t_vec3 n, t_vec3 l)
{
	return (vec3_subtract(vec3_scale(n, 2.0 * vec3_dot(n, l)), l));
}

t_color	specular_light(t_scene *scene, t_hit *hit,
						t_light *light, t_vec3 light_direction)
{
	t_vec3	view;
	t_vec3	reflected;
	double	alignment;
	double	strength;

	view = vec3_normal(vec3_subtract(scene->camera.pos, hit->point));
	reflected = reflect(hit->normal, light_direction);
	alignment = fmin(1.0, fmax(0.0, vec3_dot(reflected, view)));
	alignment *= alignment;
	alignment *= alignment;
	alignment *= alignment;
	alignment *= alignment;
	alignment *= alignment;
	strength = 0.5 * light->ratio * alignment;
	return (apply_light((t_color){255, 255, 255}, light->color, strength));
}
