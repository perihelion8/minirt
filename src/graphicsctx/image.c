/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:56:04 by abazzoun          #+#    #+#             */
/*   Updated: 2026/08/18 21:56:05 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "image_internal.h"
#include "mlx.h"

int	image_init(t_image *image, void *mlx, int width, int height)
{
	image->width = width;
	image->height = height;
	image->img = mlx_new_image(mlx, width, height);
	if (image->img == NULL)
		return (0);
	image->addr = mlx_get_data_addr(image->img, &image->bpp,
			&image->line_len, &image->pixel_order);
	if (image->addr == NULL)
	{
		mlx_destroy_image(mlx, image->img);
		image->img = NULL;
		return (0);
	}
	return (1);
}

int	image_width(const t_image *image)
{
	return (image->width);
}

int	image_height(const t_image *image)
{
	return (image->height);
}

void	image_put_pixel(t_image *img, int x, int y, t_color color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color_rgb_hex(color.r, color.g, color.b);
}
