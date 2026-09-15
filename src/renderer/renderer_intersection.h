/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_intersection.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:52:40 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/15 09:34:49 by abazzoun         ###   ########.fr       */
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
}	t_hit;

t_hit	no_hit(void);
t_hit	make_hit(double t, t_vec3 point, t_vec3 normal, t_color color);
t_hit	find_closest_intersection(t_scene *scene, t_ray ray);
t_hit	find_intersection(t_scene *scene, t_ray ray);
t_hit	intersect_sp(t_ray ray, const t_sphere *sphere);
t_hit	intersect_cy(t_ray ray, const t_cylinder *cylinder);
t_hit	intersect_hp(t_ray ray, const t_hyperboloid *hp);
t_hit	intersect_pl(t_ray ray, const t_plane *plane);

#endif
