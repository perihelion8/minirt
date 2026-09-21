/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_ray.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:53:47 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/18 02:05:30 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_RAY_H
# define RENDERER_RAY_H

# include "scene/camera.h"

typedef struct s_grid
{
	int		x;
	int		y;
	int		width;
	int		height;
	double	half_viewport_width;
	double	half_viewport_height;
	t_vec3	step_x;
	t_vec3	step_y;
	t_vec3	first_direction_in_row;
	t_vec3	current_direction;
}				t_grid;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}				t_ray;

#endif
