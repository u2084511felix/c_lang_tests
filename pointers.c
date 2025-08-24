#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//NOTE: testing codetags [CT-1-852592b3]
//

//TODO: testing. [CT-1-40ba4d33]

//FIX: .... [CT-2-6a58eca7]

struct shape2d {
    int w;
    int l;
};

struct shape3d {
    int h;
    int vol;
};

struct shape2dp {
    int* w;
    int* l;
};

struct shape3dp {
    int* h;
    int* vol;
};


int get_vol(int len, int width, int height) {
    int surface_area = len * width;
    int vol = surface_area * height;
    return vol;
}

int get_vol_inc(int len, int width, int height) {
    len += 1;
    width += 1;
    height += 1;

    int surface_area = len * width;
    int vol = surface_area * height;
    return vol;
}

int get_volp(int* len, int* width, int* height) {
    *len += 1;
    *width += 1;
    *height += 1;

    int surface_area = *len * *width;
    int vol = surface_area * *height;
    return vol;
}


int* pget_vol(int len, int width, int height) {
    int surface_area = len * width;
    int vol = surface_area * height;
    int* volp = &vol;
    return volp;
}

void print_vals(int l, int w, int h, int v){
    printf("Length: %i, Width: %i, Height: %i, Vol: %i\n", l, w, h, v);
}

int main() {

    // char a = 'A';
    // char *b = "Hello";
    // printf("char a: %c\n", a);
    // printf("char a address: %p\n", &a);
    //
    // printf("char b pointer: %s\n", b);
    // printf("char b pointer value: %c\n", *b);
    // printf("char b pointer address: %p\n", &b);

    // int c = 42;
    // int *d;
    // d = &c;
    // *d += 10;
    // printf("int c: %i\n", c);
    // printf("int c address: %p\n", &c);

    // printf("int d pointer value: %i\n", *d);
    // printf("int d points to address (same as c): %p\n", d);
    // printf("int d pointer address: %p\n", &d);


    int w = 5;
    int l = 5;
    int h = 2;
    int* pw = &w;
    int* pl = &l;
    int* ph = &h;

    int v = get_vol(l, w, h); 
    int* pv = &v;
    print_vals(l, w, h, v);  // Length: 5, Width: 5, Height: 2, Vol: 50
    
    v = get_vol_inc(l, w, h);
    print_vals(l, w, h, v);  // Length: 5, Width: 5, Height: 2, Vol: 108
    
    *pv = get_volp(pw, pl, ph);
    print_vals(l, w, h, v); // Length: 6, Width: 6, Height: 3, Vol: 108

    *pv = get_volp(&w, &l, &h);
    print_vals(l, w, h, v); // Length: 7, Width: 7, Height: 4, Vol: 196
    
    struct shape2d square;
    square.l = 11;
    square.w = 3;

    struct shape3d cube;
    cube.h = 3;
    cube.vol = square.w * square.l * cube.h;

    print_vals(square.l, square.w, cube.h, cube.vol);

    // Struct containing pointers
    struct shape2dp psquare;
    psquare.l = &square.l;
    psquare.w = &square.w;

    struct shape3dp pcube;
    pcube.h = &cube.h;
    pcube.vol = &cube.vol;

    print_vals(square.l, square.w, cube.h, cube.vol);
    print_vals(*psquare.l, *psquare.w, *pcube.h, *pcube.vol);

    // Pointer struct with non pointer mem vars
    struct shape2d* pshape2d = &square;
    pshape2d->l = *psquare.l;
    pshape2d->w = *psquare.w;

    struct shape3d* pshape3d =&cube;
    pshape3d->h = *pcube.h;
    pshape3d->vol = get_volp(&pshape2d->l, &pshape2d->w, &pshape3d->h);

    square.l += 2;
    *psquare.l += -1;
    pshape2d->w += -3;

    print_vals(square.l, square.w, cube.h, cube.vol);
    print_vals(*psquare.l, *psquare.w, *pcube.h, *pcube.vol);


    print_vals(pshape2d->l, pshape2d->w, pshape3d->h, pshape3d->vol);

}
