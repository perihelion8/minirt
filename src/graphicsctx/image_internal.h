/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 12:56:59 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/12 15:58:37 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_INTERNAL_H
# define IMAGE_INTERNAL_H

# include "image.h"
# include "color.h"

typedef struct s_image
{
	int		width;
	int		height;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		pixel_order;
}	t_image;

int		image_init(t_image *image, void *mlx, int width, int height);

#endif
