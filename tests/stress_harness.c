/* Standalone test harness; does not open a display. */
#include <assert.h>
#include <errno.h>
#include <dirent.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "loader.h"
#include "parser.h"
#include "renderer.h"
#include "renderer_ray.h"
#include "renderer_intersection.h"
#include "renderer_shade.h"

static long fail_at = -1;
static long allocations;
void *__real_malloc(size_t n);
void *__wrap_malloc(size_t n)
{
    if (++allocations == fail_at) { errno = ENOMEM; return NULL; }
    return __real_malloc(n);
}
typedef struct s_test_image { int width, height; unsigned char data[160*120*3]; } t_test_image;
int image_width(const void *p) { return ((const t_test_image *)p)->width; }
int image_height(const void *p) { return ((const t_test_image *)p)->height; }
void image_put_pixel(void *p, int x, int y, t_color c)
{
    t_test_image *im=p;
    assert(x>=0 && x<im->width && y>=0 && y<im->height);
    assert(c.r>=0 && c.r<=255 && c.g>=0 && c.g<=255 && c.b>=0 && c.b<=255);
    int i=(y*im->width+x)*3;
    im->data[i]=c.r; im->data[i+1]=c.g; im->data[i+2]=c.b;
}
static void finite_vec(t_vec3 p) { assert(isfinite(p.x) && isfinite(p.y) && isfinite(p.z)); }
static void check_hit(t_hit h)
{
    if (!h.hit) return;
    assert(isfinite(h.t) && h.t>0);
    finite_vec(h.point); finite_vec(h.normal);
    assert(fabs(vec3_length(h.normal)-1)<1e-6);
}
static void close_to(double a,double b) { assert(fabs(a-b)<1e-7); }
static uint32_t rng=1234567;
static double random_number(void) { rng=1664525*rng+1013904223; return (rng/(double)UINT32_MAX)*12-6; }
static void lighting(void)
{
    t_scene s={0}; t_light lights[2]={0}; t_shape blocker={0};
    t_hit h={1,0,{0,0,0},{0,0,1},{255,255,255}};
    s.ambient.ratio=0.1; s.ambient.color=(t_color){255,255,255};
    lights[0].pos=(t_vec3){0,0,10}; lights[0].ratio=0.5; lights[0].color=(t_color){255,0,0};
    lights[1].pos=(t_vec3){10,0,10}; lights[1].ratio=0.5; lights[1].color=(t_color){0,0,255};
    lights[0].node.next=&lights[1].node; s.lightll=lights;
    t_color c=shade_hit(&s,&h); assert(c.r==153 && c.g==25 && c.b==115);
    blocker.type=SPHERE; blocker.sphere.pos=(t_vec3){0,0,5}; blocker.sphere.diameter=2;
    s.shapell=&blocker; c=shade_hit(&s,&h); assert(c.r==25 && c.g==25 && c.b==115);
    blocker.sphere.pos.z=20; c=shade_hit(&s,&h); assert(c.r==153 && c.b==115);
    lights[0].ratio=0; lights[1].ratio=0; c=shade_hit(&s,&h); assert(c.r==25 && c.g==25 && c.b==25);
    lights[0].pos.z=-10; lights[0].ratio=1; c=shade_hit(&s,&h); assert(c.r==25);
    lights[0].pos.z=0; c=shade_hit(&s,&h); assert(c.r==25);
    puts("lighting: colored mixing, independent shadows, light bounds, zero strength passed");
}
static void geometry(void)
{
    t_sphere sp={{0,0,0},{255,255,255},2};
    t_plane pl={{0,0,0},{0,1,0},{255,255,255}};
    t_cylinder cy={0};
    cy.axis=(t_vec3){0,0,1}; cy.diameter=2; cy.height=2;
    vec3_basis(&cy.axis,&cy.right,&cy.up);
    t_hit h=intersect_sp((t_ray){{3,0,0},{-1,0,0}},&sp);
    assert(h.hit); close_to(h.t,2);
    h=intersect_sp((t_ray){{0,0,0},{1,0,0}},&sp); assert(h.hit); close_to(h.t,1);
    h=intersect_sp((t_ray){{1,-3,0},{0,1,0}},&sp); assert(h.hit); close_to(h.t,3);
    assert(!intersect_sp((t_ray){{2,-3,0},{0,1,0}},&sp).hit);
    h=intersect_pl((t_ray){{0,3,0},{0,-1,0}},&pl); assert(h.hit); close_to(h.t,3);
    assert(!intersect_pl((t_ray){{0,3,0},{1,0,0}},&pl).hit);
    h=intersect_cy((t_ray){{0,0,3},{0,0,-1}},&cy); assert(h.hit); close_to(h.t,2);
    h=intersect_cy((t_ray){{3,0,0},{-1,0,0}},&cy); assert(h.hit); close_to(h.t,2);
#ifdef BONUS
    t_hyperboloid hp={{0,0,0},{0,0,1},{255,255,255},2,2};
    h=intersect_hp((t_ray){{-2,0,0},{1,0,1}},&hp); assert(h.hit); close_to(h.t,0.75);
    h=intersect_hp((t_ray){{0,0,3},{0,0,-1}},&hp); assert(h.hit); close_to(h.t,2);
    h=intersect_hp((t_ray){{1,-3,0},{0,1,0}},&hp); assert(h.hit); close_to(h.t,3);
#endif
    t_scene inside={0}; t_shape shape={0}; t_light light={0};
    shape.type=SPHERE; shape.sphere=sp;
    light.pos=(t_vec3){0,0,0}; light.ratio=1; light.color=(t_color){255,255,255};
    inside.shapell=&shape; inside.lightll=&light;
    h=find_closest_intersection(&inside,(t_ray){{0,0,0},{0,0,1}});
    t_color lit=shade_hit(&inside,&h);
    assert(lit.r==255 && lit.g==255 && lit.b==255);
    t_light dim[1000]={0};
    for(int i=0;i<1000;i++) {
        dim[i].ratio=0.001; dim[i].color=(t_color){255,255,255};
        if(i<999) dim[i].node.next=&dim[i+1].node;
    }
    inside.lightll=dim; lit=shade_hit(&inside,&h);
    assert(lit.r>=254 && lit.g>=254 && lit.b>=254);
    for(int i=0;i<100000;i++) {
        t_ray r={{random_number(),random_number(),random_number()},
                 {random_number(),random_number(),random_number()}};
        r.direction=vec3_normal(r.direction);
        h=intersect_sp(r,&sp); check_hit(h);
        if(h.hit) close_to(vec3_length_squared(h.point),1);
        h=intersect_pl(r,&pl); check_hit(h);
        if(h.hit) close_to(h.point.y,0);
        h=intersect_cy(r,&cy); check_hit(h);
        if(h.hit) assert(fabs(fabs(h.point.z)-1)<1e-7 || fabs(h.point.x*h.point.x+h.point.y*h.point.y-1)<1e-7);
#ifdef BONUS
        h=intersect_hp(r,&hp); check_hit(h);
        /* Independent long-double root/cap reference, canonical axis. */
        long double a=(long double)r.direction.x*r.direction.x+(long double)r.direction.y*r.direction.y-(long double)r.direction.z*r.direction.z;
        long double b=2*((long double)r.origin.x*r.direction.x+(long double)r.origin.y*r.direction.y-(long double)r.origin.z*r.direction.z);
        long double c=(long double)r.origin.x*r.origin.x+(long double)r.origin.y*r.origin.y-(long double)r.origin.z*r.origin.z-1;
        long double disc=b*b-4*a*c, best=1e100L;
        if(disc>=0 && a!=0) for(int j=-1;j<=1;j+=2) {
            long double t=(-b+j*sqrtl(disc))/(2*a), z=r.origin.z+t*r.direction.z;
            if(t>1e-9L && fabsl(z)<=1 && t<best) best=t;
        }
        if(r.direction.z!=0) for(int j=-1;j<=1;j+=2) {
            long double t=(j-r.origin.z)/(long double)r.direction.z;
            long double x=r.origin.x+t*r.direction.x, y=r.origin.y+t*r.direction.y;
            if(t>1e-9L && x*x+y*y<=2 && t<best) best=t;
        }
        assert(h.hit==(best<1e99L));
        if(h.hit) assert(fabsl(h.t-best)<1e-7L);
        /* Translation and rotation must preserve ray distance. */
        t_hyperboloid moved=hp; moved.pos=(t_vec3){2,3,4}; moved.axis=(t_vec3){0,1,0};
        t_ray rr={{r.origin.x+2,r.origin.z+3,-r.origin.y+4},{r.direction.x,r.direction.z,-r.direction.y}};
        t_hit hh=intersect_hp(rr,&moved); check_hit(hh); assert(h.hit==hh.hit);
        if(h.hit) close_to(h.t,hh.t);
#endif
    }
    puts("geometry: 100000 randomized rays passed");
}
static void scan_scene(t_scene *s)
{
    for(int y=0;y<12;y++) for(int x=0;x<16;x++) {
        t_ray r=ray_generate(&s->camera,(t_pixel_coord){x,y},16,12);
        finite_vec(r.direction);
        t_hit h=find_closest_intersection(s,r); check_hit(h);
        if(h.hit) { t_color c=shade_hit(s,&h); assert(c.r>=0 && c.r<=255 && c.g>=0 && c.g<=255 && c.b>=0 && c.b<=255); }
    }
}
static int fd_count(void)
{
    DIR *d=opendir("/proc/self/fd"); assert(d); int n=0;
    while(readdir(d)) n++;
    closedir(d); return n;
}
int main(int argc,char **argv)
{
    if(argc==2 && !strcmp(argv[1],"geometry")) { lighting(); geometry(); return 0; }
    if(argc==3 && !strcmp(argv[1],"alloc")) {
        t_scene s;
        allocations=0; assert(loader_rt(&s,argv[2])); scene_destroy(&s);
        long count=allocations;
        for(long i=1;i<=count;i++) {
            allocations=0; fail_at=i;
            int ok=loader_rt(&s,argv[2]);
            scene_destroy(&s); scene_destroy(&s);
            fail_at=-1;
            assert(!ok);
        }
        printf("allocation failures: %ld passed\n",count); return 0;
    }
    if(argc==4 && !strcmp(argv[1],"render")) {
        t_scene s; assert(loader_rt(&s,argv[2]));
        t_test_image im={.width=160,.height=120}; render_scene(&s,&im);
        FILE *f=fopen(argv[3],"wb"); assert(f); fprintf(f,"P6\n160 120\n255\n");
        assert(fwrite(im.data,1,sizeof(im.data),f)==sizeof(im.data)); fclose(f);
        scene_destroy(&s); return 0;
    }
    int fds=fd_count();
    for(int i=1;i<argc;i++) {
        t_scene s; int ok=loader_rt(&s,argv[i]);
        if(ok) scan_scene(&s);
        printf("%d\t%s\n",ok,argv[i]);
        scene_destroy(&s); scene_destroy(&s);
        assert(fd_count()==fds);
    }
    return 0;
}
