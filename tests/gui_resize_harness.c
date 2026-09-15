#define _DEFAULT_SOURCE
#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "loader.h"
#include "../src/engine/engine_internal.h"
#include "mlx_int.h"
static long calls,fail,second;
void *__real_malloc(size_t n);
void *__real_calloc(size_t n,size_t size);
static int failed(void) { ++calls; return calls==fail || calls==second || (fail<0 && calls>=-fail); }
void *__wrap_malloc(size_t n) { if(failed()) { errno=ENOMEM; return NULL; } return __real_malloc(n); }
void *__wrap_calloc(size_t n,size_t size) { if(failed()) { errno=ENOMEM; return NULL; } return __real_calloc(n,size); }
int main(int argc,char **argv)
{
    assert(argc==3); t_scene scene; t_engine engine;
    assert(loader_rt(&scene,"tests/fullscreen.rt")); assert(engine_init(&engine,&scene));
    t_graphicsctx *ctx=engine.graphics; t_xvar *mlx=ctx->mlx; t_win_list *win=ctx->win;
    XResizeWindow(mlx->display,win->window,800,600); XFlush(mlx->display);
    XWindowAttributes attr={0};
    for(int i=0;i<200;i++) { usleep(10000); XGetWindowAttributes(mlx->display,win->window,&attr); if(attr.width==800 && attr.height==600) break; }
    assert(attr.width==800 && attr.height==600);
    void *old=ctx->img.img; calls=0;fail=atol(argv[1]);second=atol(argv[2]);
    engine_resize(&engine); long count=calls;
    if(engine.running) {
        assert(ctx->img.img!=old && ctx->width==800 && ctx->height==600);
        assert(scene.width==800 && scene.height==600);
        assert(fabs(scene.camera.half_viewport_height-scene.camera.half_viewport_width*0.75)<1e-12);
        assert(graphicsctx_sync_size(ctx)==0);
    } else { assert(ctx->img.img==old && ctx->width==960 && ctx->height==720); }
    int ok=engine.running;
    engine_destroy(&engine);scene_destroy(&scene);
    printf("resize allocations=%ld fail=%ld second=%ld resized=%d\n",count,fail,second,ok);
}
