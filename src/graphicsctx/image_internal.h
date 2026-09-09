/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:56:18 by abazzoun          #+#    #+#             */
/*   Updated: 2026/08/18 21:56:19 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_INTERNAL_H
# define IMAGE_INTERNAL_H

# include "image.h"

struct s_image
{
	int		width;
	int		height;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		pixel_order;
};

int	image_init(t_image *image, void *mlx, int width, int height);

#endif
