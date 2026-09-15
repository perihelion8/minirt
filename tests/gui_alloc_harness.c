/* Fail each malloc performed by application/MiniLibX during GUI startup. */
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "engine.h"
#include "loader.h"
static long calls, fail, fail_second;
void *__real_malloc(size_t n);
void *__wrap_malloc(size_t n)
{
    if(++calls==fail || calls==fail_second || (fail<0 && calls>=-fail)) { errno=ENOMEM; return NULL; }
    return __real_malloc(n);
}
void *__real_calloc(size_t n,size_t size);
void *__wrap_calloc(size_t n,size_t size)
{
    if(++calls==fail || calls==fail_second || (fail<0 && calls>=-fail)) { errno=ENOMEM; return NULL; }
    return __real_calloc(n,size);
}
int main(int argc,char **argv)
{
    assert(argc==3 || argc==4);
    t_scene scene; t_engine engine;
    assert(loader_rt(&scene,argv[2]));
    calls=0; fail=atol(argv[1]);
    if(argc==4) fail_second=atol(argv[3]);
    int ok=engine_init(&engine,&scene);
    long count=calls;
    engine_destroy(&engine); scene_destroy(&scene);
    printf("GUI allocations=%ld fail=%ld initialized=%d\n",count,fail,ok);
    return 0;
}
