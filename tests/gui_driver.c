#define _DEFAULT_SOURCE
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
#include <assert.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
static Display *d;
static pid_t child;
static Window excluded[256];
static int nexcluded;
static void cleanup(void) { if(child>0) { kill(child,SIGTERM); waitpid(child,NULL,0); } }
static void aborted(int sig) { cleanup(); _exit(128+sig); }
static Window find_window(Window parent,int initial)
{
    Window root,back,*children=NULL,found=0; unsigned int n=0;
    if(!XQueryTree(d,parent,&root,&back,&children,&n)) return 0;
    for(unsigned int i=0;i<n;i++) {
        char *name=NULL;
        if(XFetchName(d,children[i],&name) && name && !strcmp(name,"miniRT")) {
            int old=0;
            for(int j=0;j<nexcluded;j++) if(children[i]==excluded[j]) old=1;
            if(initial) { if(nexcluded<256) excluded[nexcluded++]=children[i]; }
            else if(!old) found=children[i];
        }
        if(name) XFree(name);
        if(!found) found=find_window(children[i],initial);
        if(found && !initial) break;
    }
    if(children) XFree(children);
    return found;
}
static uint64_t capture(Window w,const char *path)
{
    XWindowAttributes a; XGetWindowAttributes(d,w,&a);
    XImage *im=XGetImage(d,w,0,0,a.width,a.height,AllPlanes,ZPixmap); assert(im);
    FILE *f=path?fopen(path,"wb"):NULL;
    if(f) fprintf(f,"P6\n%d %d\n255\n",a.width,a.height);
    uint64_t hash=1469598103934665603ULL; unsigned long nonblack=0;
    int step_x=f?1:(a.width>160?a.width/160:1);
    int step_y=f?1:(a.height>120?a.height/120:1);
    for(int y=0;y<a.height;y+=step_y) for(int x=0;x<a.width;x+=step_x) {
        unsigned long p=XGetPixel(im,x,y); nonblack+=(p!=0);
        hash=(hash^p)*1099511628211ULL;
        if(f) { unsigned char rgb[3]={p>>16,p>>8,p}; fwrite(rgb,1,3,f); }
    }
    if(f) fclose(f);
    XDestroyImage(im);
    return nonblack?hash:0;
}
static uint64_t settled(Window w)
{
    uint64_t last=0,now; int stable=0;
    for(int i=0;i<600;i++) {
        usleep(200000); XSync(d,False); now=capture(w,NULL);
        if(now && now==last) stable++; else stable=0;
        if(stable>=5) return now;
        last=now;
    }
    return last;
}
static void key(Window w,int type,KeySym sym)
{
    XEvent e={0}; e.xkey.type=type; e.xkey.display=d; e.xkey.window=w;
    e.xkey.root=DefaultRootWindow(d); e.xkey.same_screen=True;
    e.xkey.keycode=XKeysymToKeycode(d,sym);
    XSendEvent(d,w,False,type==KeyPress?KeyPressMask:KeyReleaseMask,&e); XFlush(d);
}
static void move_until_frame_changes(Window w,KeySym sym,uint64_t before)
{
    XSetInputFocus(d,w,RevertToParent,CurrentTime); XSync(d,False);
    usleep(200000); key(w,KeyPress,sym);
    for(int i=0;i<100;i++) {
        usleep(100000);
        if(capture(w,NULL)!=before) break;
    }
    key(w,KeyRelease,sym);
}
static int is_fullscreen(Window w)
{
    Atom actual,fs=XInternAtom(d,"_NET_WM_STATE_FULLSCREEN",False);
    unsigned long count,left; int format; unsigned char *data=NULL; int found=0;
    assert(XGetWindowProperty(d,w,XInternAtom(d,"_NET_WM_STATE",False),0,128,False,XA_ATOM,&actual,&format,&count,&left,&data)==Success);
    if(actual==XA_ATOM && format==32) for(unsigned long i=0;i<count;i++) if(((Atom *)data)[i]==fs) found=1;
    if(data) XFree(data);
    return found;
}
static void fullscreen_state(Window w,int wanted)
{
    key(w,KeyPress,XK_F11); key(w,KeyRelease,XK_F11);
    for(int i=0;i<1200;i++) {
        usleep(100000); XSync(d,False);
        if(is_fullscreen(w)==wanted) return;
    }
    assert(!"fullscreen state did not change");
}
static void fullscreen_test(Window w,const char *path,int keep)
{
    XWindowAttributes original,full,restored;
    XGetWindowAttributes(d,w,&original);
    for(int cycle=0;cycle<2;cycle++) {
        fullscreen_state(w,1); assert(settled(w));
        XGetWindowAttributes(d,w,&full);
        for(int i=0;i<1200 && (full.width!=DisplayWidth(d,DefaultScreen(d)) || full.height!=DisplayHeight(d,DefaultScreen(d)));i++) {
            usleep(100000); XGetWindowAttributes(d,w,&full);
        }
        printf("fullscreen geometry: original=%dx%d actual=%dx%d state=%d\n",original.width,original.height,full.width,full.height,is_fullscreen(w)); fflush(stdout);
        assert(is_fullscreen(w) && full.width==DisplayWidth(d,DefaultScreen(d)) && full.height==DisplayHeight(d,DefaultScreen(d)));
        /* Check the newly exposed lower-right area is rendered, not black. */
        int filled=0;
        for(int i=0;i<1200 && !filled;i++) {
            XImage *im=XGetImage(d,w,full.width-2,full.height-2,1,1,AllPlanes,ZPixmap);
            assert(im); filled=XGetPixel(im,0,0)!=0; XDestroyImage(im);
            if(!filled) usleep(100000);
        }
        assert(filled);
        char filename[4096]; snprintf(filename,sizeof(filename),"%s.fullscreen.ppm",path); capture(w,filename);
        if(keep && cycle==1) break;
        fullscreen_state(w,0); assert(settled(w));
        XGetWindowAttributes(d,w,&restored);
        assert(restored.width==original.width && restored.height==original.height);
    }
    printf("fullscreen: repeated toggle, rendered edges, restoration PASS (%dx%d -> %dx%d)\n",original.width,original.height,full.width,full.height); fflush(stdout);
}
int main(int argc,char **argv)
{
    /* mode screenshot command [args...] */
    assert(argc>=4); d=XOpenDisplay(NULL); if(!d) { fputs("No X display\n",stderr); return 77; }
    atexit(cleanup); signal(SIGABRT,aborted); find_window(DefaultRootWindow(d),1);
    child=fork(); assert(child>=0);
    if(!child) { execvp(argv[3],argv+3); _exit(127); }
    Window w=0;
    for(int i=0;i<200 && !w;i++) { usleep(100000); w=find_window(DefaultRootWindow(d),0); }
    assert(w); XRaiseWindow(d,w); XFlush(d);
    uint64_t initial=settled(w); assert(initial);
    capture(w,argv[2]); printf("initial frame: %llu\n",(unsigned long long)initial); fflush(stdout);
    if(!strcmp(argv[1],"exercise") || !strncmp(argv[1],"fullscreen",10))
        fullscreen_test(w,argv[2],!strcmp(argv[1],"fullscreen_close"));
    if(!strcmp(argv[1],"exercise")) {
        move_until_frame_changes(w,XK_w,initial);
        uint64_t moved=settled(w); assert(moved && moved!=initial);
        move_until_frame_changes(w,XK_Right,moved);
        uint64_t rotated=settled(w); assert(rotated && rotated!=moved);
        key(w,KeyPress,XK_a); usleep(200000);
        XEvent focus={0}; focus.xfocus.type=FocusOut; focus.xfocus.display=d; focus.xfocus.window=w;
        focus.xfocus.mode=NotifyNormal; focus.xfocus.detail=NotifyNonlinear;
        XSendEvent(d,w,False,FocusChangeMask,&focus); XFlush(d);
        uint64_t stopped=settled(w); usleep(500000); assert(capture(w,NULL)==stopped);
        XClearArea(d,w,0,0,0,0,True); XFlush(d);
        uint64_t exposed=settled(w);
        printf("expose restore: %s\n",exposed==stopped?"PASS":"FAIL"); fflush(stdout);
        if(exposed!=stopped) { key(w,KeyPress,XK_Escape); return 2; }
        XUnmapWindow(d,w); XFlush(d); usleep(200000); XMapRaised(d,w); XFlush(d);
        assert(settled(w)==stopped);
        puts("movement, rotation, focus loss, expose, unmap/remap: PASS");
    }
    if(!strcmp(argv[1],"close") || !strcmp(argv[1],"fullscreen_close")) {
        XEvent e={0}; e.xclient.type=ClientMessage; e.xclient.window=w;
        e.xclient.message_type=XInternAtom(d,"WM_PROTOCOLS",False); e.xclient.format=32;
        e.xclient.data.l[0]=XInternAtom(d,"WM_DELETE_WINDOW",False); e.xclient.data.l[1]=CurrentTime;
        XSendEvent(d,w,False,NoEventMask,&e); XFlush(d);
    } else key(w,KeyPress,XK_Escape);
    int status=0,done=0;
    for(int i=0;i<600;i++) { if(waitpid(child,&status,WNOHANG)==child) { done=1; child=0; break; } usleep(100000); }
    assert(done && WIFEXITED(status));
    printf("GUI exit: %d\n",WEXITSTATUS(status)); XCloseDisplay(d);
    return WEXITSTATUS(status);
}
