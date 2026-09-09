#ifndef VECTOR_H
# define VECTOR_H

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_subtract(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(t_vec3 v, double scalar);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
t_vec3	vec3_normalize(t_vec3 vector);
double	vec3_dot(t_vec3 a, t_vec3 b);
double	vec3_length(t_vec3 v);
double	vec3_length_squared(t_vec3 v);
int		vec3_are_parallel(t_vec3 a, t_vec3 b);
int		vec3_basis(t_vec3 *forward, t_vec3 *right, t_vec3 *up);

#endif
