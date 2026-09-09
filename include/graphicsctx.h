#ifndef GRAPHICSCTX_H
# define GRAPHICSCTX_H

# include "image.h"

typedef struct s_graphicsctx t_graphicsctx;

typedef int	(*t_key_hook)(int keycode, void *param);
typedef int	(*t_loop_hook)(void *param);

t_graphicsctx	*graphicsctx_create(void);
t_image			*graphicsctx_image(t_graphicsctx *ctx);
void			graphicsctx_present(t_graphicsctx *ctx);
void			graphicsctx_stop(t_graphicsctx *ctx);
void			graphicsctx_destroy(t_graphicsctx *ctx);
void			graphicsctx_run(t_graphicsctx *ctx, t_key_hook key_hook,
						t_loop_hook loop_hook, void *param);

#endif
