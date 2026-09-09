/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:52:10 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/09 17:26:11 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "renderer_ray.h"

t_ray	ray_generate(const t_camera *cam, t_pixel_coord pixel,
			int width, int height)
{
	t_ray	ray;
	double	fov_scale;
	double	cam_x;
	double	cam_y;

	fov_scale = tan((cam->fov * 3.1415 / 180.0) / 2.0);
	cam_x = (2.0 * ((pixel.x + 0.5) / width) - 1.0) * fov_scale;
	cam_y = (1.0 - 2.0 * ((pixel.y + 0.5) / height))
		* fov_scale / ((double)width / (double)height);
	ray.direction = vec3_add(cam->forward, vec3_scale(cam->right, cam_x));
	ray.direction = vec3_add(ray.direction, vec3_scale(cam->up, cam_y));
	ray.direction = vec3_normalize(ray.direction);
	ray.origin = cam->pos;
	return (ray);
}
