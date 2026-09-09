#ifndef SCENE_H
# define SCENE_H

# include <stddef.h>
# include "scene/ambient.h"
# include "scene/camera.h"
# include "scene/light.h"
# include "scene/sphere.h"
# include "scene/plane.h"
# include "scene/cylinder.h"

typedef struct	s_scene
{
	t_ambient	ambient;
	t_light		light;
	t_camera	camera;
	t_sphere	*spherell;
	t_plane		*planell;
	t_cylinder	*cylinderll;
}				t_scene;

void		scene_destroy(t_scene *scene);
t_cylinder	*cylinderll_append(t_cylinder **cylinderll);
t_plane		*planell_append(t_plane **planell);
t_sphere	*spherell_append(t_sphere **spherell);

#endif
