/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 12:57:56 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/14 15:01:28 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <stddef.h>
# include "scene/ambient.h"
# include "scene/camera.h"
# include "scene/light.h"
# include "scene/sphere.h"
# include "scene/plane.h"
# include "scene/cylinder.h"
# include "scene/hyperboloid_bonus.h"
# include "linkedlist.h"

typedef enum {
		PLANE,
		SPHERE,
		CYLINDER,
		HYPERBOLOID
}	t_shape_type;

typedef struct s_shape
{
	t_nodell		node;
	t_shape_type	type;
	union {
		t_plane			plane;
		t_sphere		sphere;
		t_cylinder		cylinder;
		t_hyperboloid	hyperboloid;
	};
}	t_shape;
		
typedef struct s_scene
{
	double		width;
	double		height;
	t_ambient	ambient;
	t_camera	camera;
	t_light		*lightll;
	t_shape		*shapell;
}	t_scene;

void	scene_init(t_scene *scene);
void	scene_destroy(t_scene *scene);

#endif
