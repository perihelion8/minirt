/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_intersection.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:52:40 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 04:57:11 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_INTERSECTION_H
# define RENDERER_INTERSECTION_H

# include "scene.h"
# include "color.h"
# include "renderer_ray.h"

typedef struct s_hit
{
	int				hit;
	double			t;
	t_vec3			point;
	t_vec3			normal;
	t_color			color;
	t_shape_type	shape;
	int				index;
}	t_hit;

t_hit	no_hit(void);
t_hit	find_closest_intersection(t_scene *scene, t_ray *ray);
int		find_intersection(t_scene *scene, t_ray *ray, double max_distance);
double	intersect_sp(t_ray *ray, t_sphere *sphere);
double	intersect_cy(t_ray *ray, t_cylinder *cylinder);
double	intersect_pl(t_ray *ray, t_plane *plane);
double	intersect_hb(t_ray *ray, t_hyperboloid *hb);
void	hit_cy(t_ray *ray, t_cylinder *cy, t_hit *hit);
void	hit_hb(t_ray *ray, t_hyperboloid *hb, t_hit *hit);
void	hit_pl(t_ray *ray, t_plane *plane, t_hit *hit);
void	hit_sp(t_ray *ray, t_sphere *sp, t_hit *hit);

#endif
