#ifndef IMAGE_H
# define IMAGE_H

# include "color.h"

typedef struct s_image	t_image;

void	image_put_pixel(t_image *img, int x, int y, t_color color);
int		image_width(const t_image *image);
int		image_height(const t_image *image);

#endif
