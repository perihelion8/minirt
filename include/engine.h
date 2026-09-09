#ifndef ENGINE_H
# define ENGINE_H

# include "scene.h"

typedef struct s_engine	t_engine;

t_engine	*engine_create(t_scene *scene);
void		engine_run(t_engine *engine);
void		engine_stop(t_engine *engine);
void		engine_destroy(t_engine *engine);

#endif
