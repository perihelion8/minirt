/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_shade.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:53:57 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 12:41:19 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_SHADE_H
# define RENDERER_SHADE_H

# include "scene.h"
# include "renderer_intersection.h"

# define RENDER_SHADOW_BIAS 1e-4

t_color	shade_hit(t_scene *scene, t_hit *hit);
t_color	direct_light(t_scene *scene, t_hit *hit, t_light *light);
t_color	specular_light(t_scene *scene, t_hit *hit,
			t_light *light, t_vec3 light_direction);
t_color	spotlight(t_scene *scene, t_hit *hit, t_spotlight *spot);
int		is_shadowed(t_scene *scene, t_hit *hit, t_light *light);

#endif
