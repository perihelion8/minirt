/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:52:19 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 12:25:09 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include "renderer.h"
#include "renderer_ray.h"
#include "renderer_intersection.h"
#include "renderer_shade.h"
#include <math.h>

static void	grid_init(t_grid *grid, t_camera *cam, void *image)
{
	grid->width = image_width(image);
	grid->height = image_height(image);
	grid->half_viewport_width = tan((cam->fov * 3.1415 / 180) / 2.0);
	grid->half_viewport_height = grid->half_viewport_width
		* ((double)grid->height / grid->width);
	grid->step_x = vec3_scale(cam->right,
			2.0 * grid->half_viewport_width / grid->width);
	grid->step_y = vec3_scale(cam->up,
			-2.0 * grid->half_viewport_height / grid->height);
	grid->first_direction_in_row = vec3_subtract(cam->forward,
			vec3_scale(cam->right, grid->half_viewport_width));
	grid->first_direction_in_row = vec3_add(grid->first_direction_in_row,
			vec3_scale(cam->up, grid->half_viewport_height));
	grid->first_direction_in_row = vec3_add(grid->first_direction_in_row,
			vec3_scale(vec3_add(grid->step_x, grid->step_y), 0.5));
}

static t_color	trace_ray(t_scene *scene, t_ray *ray)
{
	t_hit	hit;

	hit = find_closest_intersection(scene, ray);
	if (!hit.hit)
		return ((t_color){0, 0, 0});
	return (shade_hit(scene, &hit));
}

void	render_scene(t_scene *scene, void *image)
{
	t_grid	grid;
	t_ray	ray;

	grid_init(&grid, &scene->camera, image);
	ray.origin = scene->camera.pos;
	grid.y = 0;
	while (grid.y < grid.height)
	{
		grid.current_direction = grid.first_direction_in_row;
		grid.x = 0;
		while (grid.x < grid.width)
		{
			ray.direction = vec3_normal(grid.current_direction);
			image_put_pixel(image, grid.x, grid.y, trace_ray(scene, &ray));
			grid.current_direction = vec3_add(grid.current_direction,
					grid.step_x);
			grid.x++;
		}
		grid.first_direction_in_row = vec3_add(grid.first_direction_in_row,
				grid.step_y);
		grid.y++;
	}
}
