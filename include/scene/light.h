#ifndef LIGHT_H
# define LIGHT_H

# include "color.h"
# include "vector.h"

typedef struct	s_light
{
	t_vec3	pos;
	t_color	color;
	double	ratio;
}				t_light;

#endif
