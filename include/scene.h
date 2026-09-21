/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 12:57:56 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 04:48:35 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <stddef.h>
# include "scene/ambient.h"
# include "scene/camera.h"
# include "scene/light.h"
# include "scene/spotlight.h"
# include "scene/shape.h"

typedef struct s_scene
{
	double		width;
	double		height;
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_spotlight	*spotlighta;
	size_t		spotlighta_len;
	t_shape		*shapea;
	size_t		shapea_len;
}	t_scene;

void	scene_init(t_scene *scene);
void	scene_destroy(t_scene *scene);
int		validate_scene(t_scene *scene);

#endif
