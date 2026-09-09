/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_intersection.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:52:40 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/09 11:37:37 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_INTERSECTION_H
# define RENDERER_INTERSECTION_H

# include "scene.h"
# include "color.h"
# include "renderer_ray.h"

typedef struct s_hit
{
	int		hit;
	double	t;
	t_vec3	point;
	t_vec3	normal;
	t_color	color;
}				t_hit;

typedef struct s_component_of_ray
{
	double	origin_right;
	double	origin_up;
	double	origin_forward;
	double	direction_right;
	double	direction_up;
	double	direction_forward;
}				t_component_of_ray;

t_hit	no_hit(void);
t_hit	make_hit(double t, t_vec3 point, t_vec3 normal, t_color color);
t_hit	find_closest_intersection(t_scene *scene, t_ray ray);
t_hit	intersect_sphere(t_ray ray, const t_sphere *sphere);
t_hit	intersect_cylinder(t_ray ray, const t_cylinder *cylinder);
t_hit	intersect_plane(t_ray ray, const t_plane *plane);

t_component_of_ray	to_cylinder_space(t_ray ray, const t_cylinder *cylinder);
t_vec3				to_world_point(const t_cylinder *cylinder, double x, double y,
			double z);
#endif
