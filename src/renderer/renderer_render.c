/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:52:19 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/12 11:13:32 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include "renderer.h"
#include "renderer_ray.h"
#include "renderer_intersection.h"
#include "renderer_shade.h"

static t_color	trace_ray(t_scene *scene, t_ray ray)
{
	t_hit	hit;

	hit = find_closest_intersection(scene, ray);
	if (!hit.hit)
		return ((t_color){0, 0, 0});
	return (shade_hit(scene, &hit));
}

void	render_scene(t_scene *scene, void *image)
{
	t_pixel_coord	pixel;
	int				width;
	int				height;
	t_ray			ray;
	t_color			color;

	width = image_width(image);
	height = image_height(image);
	pixel.y = 0;
	while (pixel.y < height)
	{
		pixel.x = 0;
		while (pixel.x < width)
		{
			ray = ray_generate(&scene->camera, pixel, width, height);
			color = trace_ray(scene, ray);
			image_put_pixel(image, pixel.x, pixel.y, color);
			pixel.x++;
		}
		pixel.y++;
	}
}
