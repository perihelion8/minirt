#ifndef CYLINDER_H
# define CYLINDER_H

# include "color.h"
# include "vector.h"

typedef struct	s_cylinder
{
	t_vec3				pos;
	t_vec3				axis;
	t_vec3				right;
	t_vec3				up;
	t_color				color;
	double				diameter;
	double				height;
	struct s_cylinder	*next;
}				t_cylinder;

#endif
