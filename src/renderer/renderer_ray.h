/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_ray.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:53:47 by abazzoun          #+#    #+#             */
/*   Updated: 2026/08/19 04:24:45 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_RAY_H
# define RENDERER_RAY_H

# include "scene/camera.h"

typedef struct s_pixel_coord
{
	int	x;
	int	y;
}				t_pixel_coord;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}				t_ray;

t_ray	ray_generate(const t_camera *camera, t_pixel_coord pixel,
			int width, int height);

#endif
