/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_shade_spotlight.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 23:45:02 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 00:23:03 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_shade.h"
#include <math.h>

t_color	spotlight(t_scene *scene, t_hit *hit, t_spotlight *spot)
{
	t_vec3	from_light;
	double	alignment;
	t_light	light;

	from_light = vec3_subtract(hit->point, spot->pos);
	if (spot->brightness <= 0.0 || vec3_length_squared(from_light) == 0.0)
		return ((t_color){0, 0, 0});
	alignment = vec3_dot(vec3_normal(from_light), vec3_normal(spot->direction));
	if (alignment < spot->cutoff_cos)
		return ((t_color){0, 0, 0});
	light = (t_light){spot->pos, spot->color, spot->brightness, 1};
	return (direct_light(scene, hit, &light));
}
