/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 10:55:25 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/12 11:15:13 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

#include "color.h"

void	image_put_pixel(void *img, int x, int y, t_color color);
int		image_width(const void *image);
int		image_height(const void *image);

#endif
