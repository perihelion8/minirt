/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:52:10 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/14 12:25:12 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_ray.h"

static t_vec3	calc_direction(const t_camera *cam, double cam_x, double cam_y)
{
	t_vec3	ray_direction;

	ray_direction = vec3_add(cam->forward, vec3_scale(cam->right, cam_x));
	ray_direction = vec3_add(ray_direction, vec3_scale(cam->up, cam_y));
	ray_direction = vec3_normal(ray_direction);
	return (ray_direction);
}

t_ray	ray_generate(const t_camera *cam, t_pixel_coord pixel,
			int width, int height)
{
	t_ray	ray;
	double	cam_x;
	double	cam_y;

	cam_x = (2.0 * ((pixel.x + 0.5) / width) - 1.0)	* cam->half_viewport_width;
	cam_y = (1.0 - 2.0 * ((pixel.y + 0.5) / height))
		* cam->half_viewport_height;
	ray.direction = calc_direction(cam, cam_x, cam_y);
	ray.origin = cam->pos;
	return (ray);
}
