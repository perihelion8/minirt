/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphicsctx.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 12:57:19 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/14 11:48:48 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICSCTX_H
# define GRAPHICSCTX_H

# define WINDOW_WIDTH 960
# define WINDOW_HEIGHT 720

#include "image_internal.h"

typedef struct s_graphicsctx
{
	void	*mlx;
	void	*win;
	t_image	img;
	int		width;
	int		height;
}			t_graphicsctx;

typedef int	(*t_key_hook)(int keycode, void *param);
typedef int	(*t_hook)(void *param);

t_graphicsctx	*graphicsctx_create();
void			graphicsctx_destroy(t_graphicsctx *ctx);
void			graphicsctx_run(t_graphicsctx *ctx, t_key_hook key_hook,
					t_hook loop_hook, void *param);
void			graphicsctx_on_close(t_graphicsctx *ctx,
					t_hook close_hook, void *param);
void			graphicsctx_stop(t_graphicsctx *ctx);
void			graphicsctx_present(t_graphicsctx *ctx);
t_image			*graphicsctx_image(t_graphicsctx *ctx);

#endif
