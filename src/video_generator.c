#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <video_generator.h>

#define CLIP(X) ( (X) > 255 ? 255 : (X) < 0 ? 0 : X)
#define RGB2Y(R, G, B) CLIP(( (  66 * (R) + 129 * (G) +  25 * (B) + 128) >> 8) +  16)
#define RGB2U(R, G, B) CLIP(( ( -38 * (R) -  74 * (G) + 112 * (B) + 128) >> 8) + 128)
#define RGB2V(R, G, B) CLIP(( ( 112 * (R) -  94 * (G) -  18 * (B) + 128) >> 8) + 128)

static uint64_t numbersfont_pixel_data[] = {0x0,0x0,0xffffffff0000,0x0,0xffffff0000000000,0xffffffffffff,0x0,0x0,0xffffffffffffff00,0xff,0xffffffffffff0000,0xffffffffffffffff,0xffffffffffffffff,0xffffffff,0xffff000000000000,0xffffffffff,0x0,0xff00000000000000,0xffffffffffff,0x0,0xffff000000000000,0xffffffffffffffff,0xffffffffffffffff,0x0,0xffffffffff000000,0xffffff,0x0,0xffffff0000000000,0xffffffff,0x0,0x0,0xff00ffffff000000,0xffffffff,0x0,0x0,0xffffffffff00,0x0,0xffffffffff000000,0xffffffffffffffff,0x0,0xff00000000000000,0xffffffffffffffff,0xffffff,0xffffffffffff0000,0xffffffffffffffff,0xffffffffffffffff,0xffffffff,0xffffffffff000000,0xffffffffffffffff,0x0,0xffffff0000000000,0xffffffffffffffff,0xff,0xffff000000000000,0xffffffffffffffff,0xffffffffffffffff,0x0,0xffffffffffffff00,0xffffffffffff,0x0,0xffffffffff000000,0xffffffffffffff,0x0,0x0,0xff00ffffffff0000,0xffffffff,0x0,0x0,0xffffffffffff,0x0,0xffffffffffffff00,0xffffffffffffffff,0xffff,0xffffff0000000000,0xffffffffffffffff,0xffffffff,0xffffffffffff0000,0xffffffffffffffff,0xffffffffffffffff,0xffffffff,0xffffffffffff0000,0xffffffffffffffff,0xff,0xffffffffff000000,0xffffffffffffffff,0xffff,0xffffff0000000000,0xffffffffffffffff,0xffffffffffffffff,0xff00000000000000,0xffffffffffffffff,0xffffffffffffff,0x0,0xffffffffffff0000,0xffffffffffffffff,0x0,0x0,0xff00ffffffffff00,0xffffffff,0x0,0xff00000000000000,0xffffffffffff,0x0,0xffffffffffffffff,0xffffffffffffffff,0xffffff,0xffffffff00000000,0xffffffffffffffff,0xffffffffff,0xffffffffffff0000,0xffffffffffffffff,0xffffffffffffffff,0xffffffff,0xffffffffffffff00,0xffffffffffffffff,0xffff,0xffffffffffff0000,0xffffffffffffffff,0xffffffff,0xffffff0000000000,0xffffffffffffffff,0xffffffffffffffff,0xffff000000000000,0xffffffffffffffff,0xffffffffffffffff,0x0,0xffffffffffffffff,0xffffffffffffffff,0xffff,0x0,0xff00ffffffffffff,0xffffffff,0x0,0xff00000000000000,0xffffffffffff,0xff00000000000000,0xffffffffffffffff,0xffffffffffffffff,0xffffffff,0xffffffffff000000,0xffffffffffffffff,0xffffffffffff,0xffffffffffff0000,0xffffffffffffffff,0xffffffffffffffff,0xffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffff,0xffffffffffffff00,0xffffffffffffffff,0xffffffff,0xffffff0000000000,0xffffffffffffffff,0xffffffffffffffff,0xffff000000000000,0xffffffffffffffff,0xffffffffffffffff,0xff,0xffffffffffffffff,0xffffffffffffffff,0xffff,0xff00000000000000,0xff00ffffffffffff,0xffffffff,0x0,0xffff000000000000,0xffffffffffff,0xff00000000000000,0xffffffffffff,0xffffff0000000000,0xffffffffff,0xffffffffffff0000,0xff0000000000ffff,0xffffffffffffff,0x0,0x0,0xff00000000000000,0xffffff,0xffffffffffffff,0xffffffff00000000,0xffffff,0xffffffffffffff00,0xffff000000000000,0xffffffffff,0xffffff0000000000,0xffff,0x0,0xffffff0000000000,0xffffffff,0xffffffffff000000,0xff0000000000ffff,0xffffffffffffff,0xffffff0000000000,0xffffff,0xffff000000000000,0xffffffffffff,0x0,0x0,0xffffff0000000000,0xffffffffffff,0xffff000000000000,0xffffffffff,0xff00000000000000,0xffffffffff,0xffffffffffff0000,0x0,0xffffffffffff00,0x0,0x0,0xffff000000000000,0xff0000000000ffff,0xffffffffff,0xffff000000000000,0xffffffff,0xffffffffffff,0xff00000000000000,0xffffffffff,0xffffff0000000000,0xffff,0x0,0xffffff0000000000,0xffffff,0xffffffff00000000,0xffff00000000ffff,0xffffffffff,0xff00000000000000,0xffffffff,0xffffff0000000000,0xffffffffffff,0x0,0x0,0xffffff0000000000,0xffffffffffff,0xffff000000000000,0xffffff,0x0,0xffffffffffff,0xffffffffffff00,0x0,0xffffffffff0000,0x0,0x0,0xffffff0000000000,0xff000000000000ff,0xffffffff,0xff00000000000000,0xffffffff,0xffffffffff,0x0,0xffffffffffff,0xffffffff00000000,0xffff,0x0,0xffffffff00000000,0xffff,0xffffff0000000000,0xffff000000ffffff,0xffffffff,0xff00000000000000,0xffffffff,0xffffffffff000000,0xffffffffffff,0x0,0x0,0xffffffff00000000,0xffffffffffff,0xffffff0000000000,0xffffff,0x0,0xffffffffffff,0xffffffffff00,0x0,0xffffffffffff0000,0x0,0x0,0xffffffff00000000,0xffff000000000000,0xffffffff,0xff00000000000000,0xff0000ffffffffff,0xffffffffff,0x0,0xffffffffff00,0xffffffff00000000,0xff,0x0,0xffffffff00000000,0xff,0xffff000000000000,0xffff000000ffffff,0xffffff,0x0,0xffffffffff,0xffffffffffff0000,0xffffffffffff,0x0,0x0,0xffffffffff000000,0xffffffffffff,0xffffff0000000000,0xffff,0x0,0xffffffffff00,0xffffffffffff,0x0,0xffffffffff000000,0x0,0x0,0xffffffffff000000,0xffff000000000000,0xffffff,0x0,0xff0000ffffffffff,0xffffffff,0x0,0xffffffffff00,0xffffffff00000000,0xff,0x0,0xffffffff00000000,0xff,0xffff000000000000,0xffffff0000ffffff,0xffffff,0x0,0xffffffff00,0xffffffffffffffff,0xffffffffff00,0x0,0x0,0xffffffffffff0000,0xffffffffff00,0xffffff0000000000,0xffff,0x0,0xffffffffff00,0xffffffffff,0x0,0x0,0x0,0x0,0xffffffffff0000,0xffff000000000000,0xffffff,0x0,0xffffffffff,0xffffff00,0x0,0xffffffffff00,0xffffffff00000000,0xff,0x0,0xffffffff00000000,0xff,0xffff000000000000,0xffffff0000ffffff,0xffff,0x0,0xff0000ffffffff00,0xffffffffffffff,0xffffffffff00,0x0,0x0,0xffffffffffff0000,0xffffffffff00,0xff00000000000000,0xffff,0x0,0xffffffffff00,0xffffffffff,0x0,0x0,0x0,0x0,0xffffffff0000,0xffff000000000000,0xffffff,0x0,0xffffffffff,0x0,0x0,0xffffffffff00,0xffffffff00000000,0xff,0x0,0xffffffff00000000,0xff,0xffff000000000000,0xffffff0000ffffff,0xffff,0x0,0xff0000ffffffff00,0xffffffffff,0xffffffffff00,0x0,0x0,0xffffffffffff00,0xffffffffff00,0x0,0x0,0x0,0xffffffffff00,0xffffffffff,0x0,0x0,0x0,0x0,0xffffffffff00,0xffffff0000000000,0xffff,0x0,0xffffffffff00,0x0,0x0,0xffffffffff,0xffffffffff000000,0xff,0x0,0xffffffff00000000,0xffff,0xffffff0000000000,0xffffff0000ffffff,0xffff,0x0,0xff00ffffffffff00,0xffffff,0xffffffffff00,0x0,0x0,0xffffffffffff,0xffffffffff00,0x0,0x0,0x0,0xffffffffff00,0xffffffff,0x0,0x0,0x0,0x0,0xffffffffff,0xffffff0000000000,0xffff,0x0,0xffffffffff00,0x0,0xff00000000000000,0xffffffffff,0xffffffffff000000,0xffffffff000000ff,0xffff,0xffffff0000000000,0xffffff,0xffffff0000000000,0xffffff000000ffff,0xffff,0x0,0xff00ffffffffff00,0xff,0xffffffffff00,0x0,0x0,0xffffffffff,0xffffffffff00,0x0,0x0,0x0,0xff0000ffffffffff,0xffffffff,0xffffffffffff0000,0xff,0x0,0x0,0xffffffffff,0xffffff0000000000,0xffff,0x0,0xffffffffff00,0x0,0xffffff0000000000,0xffffffff,0xffffffffff000000,0xffffffffffff0000,0xffffffff,0xffff000000000000,0xffffffff,0xffffffffff000000,0xffffff00000000ff,0xffff,0x0,0xffffffffff00,0x0,0xffffffffff00,0x0,0xff00000000000000,0xffffffffff,0xffffffffff00,0x0,0x0,0x0,0xff0000ffffffffff,0xffffffff,0xffffffffffffffff,0xffffff,0x0,0xff00000000000000,0xffffffff,0xffffff0000000000,0xffff,0x0,0xffffffffff00,0x0,0xffffffffffffff00,0xffffff,0xffffffffff000000,0xffffffffffffff00,0xffffffffffff,0xff00000000000000,0xffffffffffffffff,0xffffffffffffffff,0xffffff0000000000,0xffff,0x0,0xffffffffff00,0x0,0xffffffffff00,0x0,0xffff000000000000,0xffffffff,0xffffffffff00,0x0,0x0,0xff00000000000000,0xff0000ffffffffff,0xffff0000ffffffff,0xffffffffffffffff,0xffffffffff,0x0,0xff00000000000000,0xffffffff,0xffffff0000000000,0xffff,0x0,0xffffffffff00,0x0,0xffffffffffffff00,0xff,0xffffffffff000000,0xffffffffffffffff,0xffffffffffffff,0x0,0xffffffffffffffff,0xffffffffffffff,0xffffff0000000000,0xffffff,0x0,0xffffffffffff,0x0,0xffffffffff00,0x0,0xffffff0000000000,0xffffff,0xffffffffff00,0x0,0x0,0xffff000000000000,0xff000000ffffffff,0xffffff00ffffffff,0xffffffffffffffff,0xffffffffffff,0x0,0xffff000000000000,0xffffff,0xffffff0000000000,0xffff,0x0,0xffffffffff00,0x0,0xffffffffffffff00,0xffffff,0xffffffffffff0000,0xffffffffffffffff,0xffffffffffffffff,0x0,0xffffffffffffff00,0xffffffffffff,0xffff000000000000,0xffffff,0xff00000000000000,0xffffffffffff,0x0,0xffffffffff00,0x0,0xffffff0000000000,0xffffff,0xffffffffff00,0x0,0x0,0xffffff0000000000,0xff00000000ffffff,0xffffff00ffffffff,0xffffffffffffffff,0xffffffffffffff,0x0,0xffff000000000000,0xffffff,0xffffff0000000000,0xffff,0x0,0xffffffffff00,0x0,0xffffffffffffff00,0xffffffff,0xffffffffffff0000,0xffff,0xffffffffffffff00,0xff00000000000000,0xffffffffffffffff,0xffffffffffffffff,0xffff000000000000,0xffffffff,0xffff000000000000,0xffffffffffff,0x0,0xffffffffff00,0x0,0xffffffff00000000,0xffff,0xffffffffff00,0x0,0x0,0xffffffff00000000,0xff0000000000ffff,0xffffffffffffffff,0xff,0xffffffffffffff,0x0,0xffffff0000000000,0xffff,0xffffff0000000000,0xffff,0x0,0xffffffffff00,0x0,0xffffffff00ffff00,0xffffffffff,0xffffffffffff0000,0x0,0xffffffffff000000,0xffff0000000000ff,0xffffffffffffffff,0xffffffffffffffff,0xff000000000000ff,0xffffffffffff,0xffffff0000000000,0xffffffffffff,0x0,0xffffffffff00,0x0,0xffffffffff000000,0xff,0xffffffffff00,0x0,0x0,0xffffffffff000000,0xff0000000000ffff,0xffffffffffffff,0x0,0xffffffffffffff00,0x0,0xffffff0000000000,0xffff,0xffffff0000000000,0xffff,0x0,0xffffffffff00,0x0,0x0,0xffffffffffff,0xffffff00000000,0x0,0xffffffff00000000,0xffffff00000000ff,0xffffffff,0xffffffffff000000,0xff0000000000ffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffff,0x0,0xffffffffff00,0x0,0xffffffffff000000,0x0,0xffffffffff00,0x0,0x0,0xffffffffffff0000,0xff000000000000ff,0xffffffffffff,0x0,0xffffffffffff0000,0x0,0xffffffff00000000,0xff,0xffffff0000000000,0xffff,0x0,0xffffffffff00,0x0,0x0,0xffffffffffff00,0x0,0x0,0xffffffff00000000,0xffffffff0000ffff,0xffff,0xffffff0000000000,0xffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffff00,0x0,0xffffffffff00,0x0,0xffffffffffff0000,0x0,0xffffffffff00,0x0,0x0,0xffffffffffffff00,0xff00000000000000,0xffffffffff,0x0,0xffffffffff000000,0xff,0xffffffff00000000,0xff,0xffffff0000000000,0xffff,0x0,0xffffffffff00,0x0,0x0,0xffffffffff0000,0x0,0x0,0xffffff0000000000,0xffffffff0000ffff,0xff,0xffff000000000000,0xffffff,0xffffffffffffff00,0xffffffffffffff,0xffffffffff00,0x0,0xffffffffff00,0x0,0xffffffffffff00,0x0,0xffffffffff00,0x0,0xff00000000000000,0xffffffffffff,0xff00000000000000,0xffffffff,0x0,0xffffffff00000000,0xff,0xffffffffff000000,0x0,0xffffff0000000000,0xffff,0x0,0xffffffffff00,0x0,0x0,0xffffffffffff0000,0x0,0x0,0xffffff0000000000,0xffffffff0000ffff,0xff,0xffff000000000000,0xffffff,0xffffffffff000000,0xffffffffff,0xffffffffff00,0x0,0xffffffffff00,0x0,0xffffffffffff,0x0,0xffffffffff00,0x0,0xffff000000000000,0xffffffffff,0xff00000000000000,0xffffffff,0x0,0xffffffff00000000,0xff,0xffffffffff000000,0x0,0xffffff0000000000,0xffff,0x0,0xffffffffff00,0x0,0x0,0xffffffffff000000,0x0,0x0,0xffffff0000000000,0xffffffffff00ffff,0x0,0xff00000000000000,0xffffffff,0xffffff0000000000,0xffffff,0xffffffffff00,0x0,0xff00ffffffffff00,0xffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffff,0xffffff0000000000,0xffffffff,0xff00000000000000,0xffffffff,0x0,0xffffffff00000000,0xff,0xffffffffff000000,0x0,0xffffff0000000000,0xffff,0x0,0xffffffffff00,0x0,0x0,0xffffffffff000000,0x0,0x0,0xffffff0000000000,0xffffffffff00ffff,0x0,0xff00000000000000,0xffffffff,0x0,0x0,0xffffffffff00,0x0,0xff00ffffffffff00,0xffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffff,0xffffffff00000000,0xffffff,0xff00000000000000,0xffffffff,0x0,0xffffffff00000000,0xff,0xffffffffff0000,0x0,0xffffff0000000000,0xffff,0x0,0xffffffffff00,0x0,0x0,0xffffffffff000000,0x0,0x0,0xffffff0000000000,0xffffffffff00ffff,0x0,0xff00000000000000,0xffffffff,0x0,0x0,0xffffffffff,0x0,0xff00ffffffffff00,0xffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffff,0xffffffffffff0000,0xffff,0x0,0xffffffff,0x0,0xffffffff00000000,0xff,0xffffffffff0000,0x0,0xffff000000000000,0xffffff,0x0,0xffffffffff,0xffffff00,0x0,0xffffffffff000000,0x0,0x0,0xffffff0000000000,0xffffffffff00ffff,0x0,0xff00000000000000,0xffffffff,0x0,0x0,0xffffffffff,0x0,0xff00ffffffffff00,0xffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffff,0xffffffffffffff00,0xff,0x0,0xffffffff,0x0,0xffffffff00000000,0xff,0xffffffffff0000,0x0,0xffff000000000000,0xffffff,0x0,0xff0000ffffffffff,0xffffffff,0x0,0xffffffffff000000,0xffffffffff00,0x0,0xffffff0000000000,0xffffffffff00ffff,0x0,0xff00000000000000,0xffffffff,0x0,0x0,0xffffffffff,0x0,0xff00ffffffffff00,0xffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffff,0xffffffffffffff,0x0,0x0,0xffffffffff,0x0,0xffffffffff000000,0xff,0xffffffffff0000,0x0,0xffff000000000000,0xffffff,0x0,0xff0000ffffffffff,0xffffffffff,0x0,0xffffffffffff0000,0xffffffffff00,0x0,0xffffffff00000000,0xffffffffff0000ff,0x0,0xff00000000000000,0xffff0000ffffffff,0xffffff,0xff00000000000000,0xffffffffff,0x0,0xffffffffff00,0x0,0x0,0x0,0xffffffffff00,0xff00000000000000,0xffffffffffff,0x0,0x0,0xffffffffff,0x0,0xffffffffff000000,0x0,0xffffffffff00,0x0,0xffff000000000000,0xffffffff,0xff00000000000000,0xff0000ffffffffff,0xffffffffff,0x0,0xffffffffff0000,0xffffffffffff00,0x0,0xffffffff00000000,0xffffffffff0000ff,0xff,0xffff000000000000,0xffff0000ffffffff,0xffffff,0xff00000000000000,0xffffffff,0x0,0xffffffffff00,0x0,0x0,0x0,0xffffffffff00,0xff00000000000000,0xffffffffff,0x0,0x0,0xffffffffff00,0x0,0xffffffffffff0000,0x0,0xffffffffff00,0x0,0xff00000000000000,0xffffffff,0xff00000000000000,0xffffffff,0xffffffffffff,0x0,0xffffffffffff00,0xffffffffff0000,0x0,0xffffffffff000000,0xffffffff000000ff,0xff,0xffff000000000000,0xffff000000ffffff,0xffffffff,0xff00000000000000,0xffffffff,0x0,0xffffffffff00,0x0,0x0,0x0,0xffffffffff00,0xffff000000000000,0xffffffff,0x0,0x0,0xffffffffffff00,0x0,0xffffffffffffff00,0x0,0xffffffffff00,0x0,0xff00000000000000,0xffffffffff,0xffff000000000000,0xffffffff,0xffffffffffffff,0x0,0xffffffffffffff,0xffffffffffff0000,0x0,0xffffffffffff0000,0xffffffff00000000,0xffff,0xffffff0000000000,0xff00000000ffffff,0xffffffffff,0xffffff0000000000,0xffffff,0x0,0xffffffffff00,0x0,0x0,0x0,0xffffffffff00,0xffffff0000000000,0xffffff,0x0,0x0,0xffffffffffff0000,0xff,0xffffffffffffff,0x0,0xffffffffff00,0x0,0x0,0xffffffffffffff,0xffffffff00000000,0xffffff,0xffffffffffffff00,0xff00000000000000,0xffffffffffff,0xffffffffff000000,0xffff,0xffffffffffffffff,0xffffff0000000000,0xffffffffff,0xffffffffff000000,0xff0000000000ffff,0xffffffffffff,0xffffffff00000000,0xffffff,0x0,0xffffffffff00,0x0,0x0,0x0,0xffffffffff00,0xffffff0000000000,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffff,0xffffffffff000000,0xffffffffffffffff,0xffffffffffff,0x0,0xffffffffff,0x0,0x0,0xffffffffffffffff,0xffffffffffffffff,0xffffff,0xffffffffffffff00,0xffffffffffffffff,0xffffffffff,0xffffffffff000000,0xffffffffffffffff,0xffffffffffffff,0xffffff0000000000,0xffffffffffffffff,0xffffffffffffffff,0xffff,0xffffffffffffffff,0xffffffffffffffff,0xffff,0x0,0xffffffffff00,0x0,0x0,0x0,0xffffffffff00,0xffffff0000000000,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffff,0xffffffff00000000,0xffffffffffffffff,0xffffffffff,0x0,0xffffffffff,0x0,0x0,0xffffffffffffff00,0xffffffffffffffff,0xffff,0xffffffffffff0000,0xffffffffffffffff,0xffffffff,0xffffffff00000000,0xffffffffffffffff,0xffffffffffff,0xffff000000000000,0xffffffffffffffff,0xffffffffffffffff,0xff,0xffffffffffffff00,0xffffffffffffffff,0xff,0x0,0xffffffffff00,0x0,0x0,0x0,0xffffffffff00,0xffffffff00000000,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffff,0xffffff0000000000,0xffffffffffffffff,0xffffffff,0x0,0xffffffffff,0x0,0x0,0xffffffffffff0000,0xffffffffffffffff,0xff,0xffffffffff000000,0xffffffffffffffff,0xffffff,0xffffff0000000000,0xffffffffffffffff,0xffffffffff,0xff00000000000000,0xffffffffffffffff,0xffffffffffffffff,0x0,0xffffffffffffff00,0xffffffffffffffff,0x0,0x0,0xffffffffff00,0x0,0x0,0x0,0xffffffffff00,0xffffffff00000000,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffff,0xffff000000000000,0xffffffffffffffff,0xffffff,0x0,0xffffffffff,0x0,0x0,0xffffffffff000000,0xffffffffffffffff,0x0,0xffffff0000000000,0xffffffffffffffff,0xffff,0xff00000000000000,0xffffffffffffffff,0xffffff,0x0,0xffffffffffffff00,0xffffffffffff,0x0,0xffffffffff000000,0xffffffffffffff,0x0,0x0,0xffffffffff00,0x0,0x0,0x0,0xffffffffff00,0xffffffff00000000,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffff,0x0,0xffffffffffffff00,0x0,0x0,0xffffffffff,0x0,0x0,0xffff000000000000,0xffffffffff,0x0,0xff00000000000000,0xffffffffffffff,0x0,0x0,0xffffffffffffff00,0xff,0x0,0xffffffff00000000,0xffffff,0x0,0xffffff0000000000,0xffffffff,0x0,0x0,0xffffffffff00,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
static int numbersfont_char_data[] = {48,109,0,25,39,3,12,31,49,239,0,15,39,6,12,31,50,28,0,26,39,2,12,31,51,135,0,25,39,3,12,31,52,0,0,27,39,1,12,31,53,161,0,25,39,3,12,31,54,55,0,26,39,2,12,31,55,82,0,26,39,2,12,31,56,187,0,25,39,3,12,31,57,213,0,25,39,3,12,31,58,255,0,5,29,5,22,15};
static int fill(video_generator* gen, int x, int y, int w, int h, int r, int g, int b);
static int add_number_string(video_generator* gen, const char* str, int x, int y);
static int add_char(video_generator* gen, video_generator_char* kar, int x, int y);

int video_generator_init(video_generator* g, int w, int h, int fps) {

  int i = 0;
  int dx = 0;
  int max_els = RXS_MAX_CHARS * 8; /* members per char */
  video_generator_char* c = NULL;

  if (!g) { return -1; } 
  if (!w) { return -2; } 
  if (!h) { return -3; } 
  if (!fps) { return -4; } 
  
  /* initalize members */
  g->frame = 0;
  g->ybytes = w * h;
  g->ubytes = (w * 0.5) * (h * 0.5);
  g->vbytes = g->ubytes;
  g->nbytes = g->ybytes + g->ubytes + g->vbytes;
  g->width = w;
  g->height = h;
  g->fps = (1.0 / fps) * 1000 * 1000;

  g->y = (uint8_t*)malloc(g->nbytes);
  g->u = g->y + g->ybytes;
  g->v = g->y + (g->ybytes + g->ubytes);

  g->planes[0] = g->y;
  g->planes[1] = g->u;
  g->planes[2] = g->v;

  g->strides[0] = w;
  g->strides[1] = w * 0.5;
  g->strides[2] = w * 0.5;

  g->step = (1.0 / (5 * fps)); /* move the bar in 5 seconds from top to bottom */
  g->perc = 0.0;
  g->fps_num = 1;
  g->fps_den = fps;

  /* initialize the characters */
  while (i < max_els) {
    c = &g->chars[dx];
    c->id = numbersfont_char_data[i++];
    c->x = numbersfont_char_data[i++];
    c->y = numbersfont_char_data[i++];
    c->width = numbersfont_char_data[i++];
    c->height = numbersfont_char_data[i++];
    c->xoffset = numbersfont_char_data[i++];
    c->yoffset = numbersfont_char_data[i++];
    c->xadvance = numbersfont_char_data[i++];
    dx++;
  }

  /* bitmap font specifics */
  g->font_w = 264;
  g->font_h = 50;
  g->font_line_height = 63;

  return 0;
}

int video_generator_clear(video_generator* g) {

  if (!g) { return -1; } 
  if (!g->width) { return -2; } 
  if (!g->height) { return -3; } 
  
  if (g->y) {
    free(g->y);
  }

  g->y = NULL;
  g->u = NULL;
  g->u = NULL;
  g->width = 0;
  g->height = 0;
  g->frame = 0;
  g->step = 0.0;
  g->perc = 0.0;
  g->fps = 0.0;
  g->ybytes = 0;
  g->ubytes = 0;
  g->vbytes = 0;
  g->nbytes = 0;

  return 0;
}

/* generates a new frame and stores it in the y, u and v members */
int video_generator_update(video_generator* g) {

  double perc;
  int text_w, text_x, text_y, i;
  int32_t bar_h, time, speed, start_y, nlines, h;
  uint64_t days, hours, minutes, seconds;
  uint32_t stride, end_y;
  char timebuf[512] = { 0 } ;
  int rc, gc, bc, yc, uc, vc, dx;
  int colors[] = { 
    255, 255, 255,  // white
    255, 255, 0,    // yellow
    0,   255, 255,  // cyan
    0,   255, 0,    // green
    255, 0,   255,  // magenta
    255, 0,   0,    // red
    0,   0,   255   // blue
  };

  if (!g) { return -1; } 
  if (!g->width) { return -2; } 
  if (!g->height) { return -3; } 

  h = g->height - 1;
  bar_h = g->height / 5;
  start_y = -bar_h + (g->perc * (h + bar_h));

  /* how many lines of the bar are visible */
  if (start_y < 0) {
    nlines = bar_h + start_y;
    start_y = 0;
  }
  else if(start_y + bar_h > h) {
    nlines = h - start_y;
  }
  else {
    nlines = bar_h;
  }

  /* increment step */
  g->perc += g->step;
  if (g->perc >= (1.0)) {
    g->perc = 0.0;
  }

  if (nlines + start_y > g->height || nlines < 0 || start_y < 0 || start_y >= g->height) {
    printf("Error: this shouldn't happen.. writing outside the buffer: %d, %d, %d\n", nlines, (nlines + start_y), start_y);
    return -1;
  }

  /* reset */
  memset(g->y, 0x00, g->ybytes);
  memset(g->u, 0x00, g->ubytes);
  memset(g->v, 0x00, g->vbytes);

  for (i = 0; i < 7; ++i) {
    dx = i * 3;
    rc = colors[dx + 0];
    gc = colors[dx + 1];
    bc = colors[dx + 2];
    fill(g, i * (g->width / 7), 0, (g->width / 7), g->height, rc, gc, bc);
  }

  rc = 255 - (g->perc * 255);
  gc = 30 + (g->perc * 235);
  bc = 150 + (g->perc * 205);
  yc = RGB2Y(rc, gc, bc);
  uc = RGB2U(rc, gc, bc);
  vc = RGB2V(rc, gc, bc);

  /* fill y channel */
  for (i = start_y; i < (start_y + nlines); ++i) {
    memset(g->y + (i * g->width), yc, g->width);
  }
  
  /* fill u and v channel */
  start_y = start_y / 2;
  stride = g->width * 0.5;
  end_y = start_y + nlines/ 2;

  for (i = start_y; i < end_y; ++i) {
    memset(g->u + i * stride, uc, stride);
    memset(g->v + i * stride, vc, stride);
  }

  seconds = (g->frame/ g->fps_den);
  minutes = (seconds / 60);
  hours = minutes / 60;
  days = hours / 24;
  minutes %= 60;
  seconds %= 60;
  hours %= 24;
  text_w = 360; /* manually measured */
  text_x = (g->width / 2) - (text_w / 2);
  text_y = (g->height / 2) - 50;

  fill(g, text_x, text_y, text_w, 100, 0, 0, 0);

  sprintf(timebuf, "%03llu:%02llu:%02llu:%02llu", days, hours, minutes, seconds);
  add_number_string(g, timebuf, text_x + 20, text_y + 20);

  g->frame++;
  return 0;
}

static int fill(video_generator* gen, int x, int y, int w, int h, int r, int g, int b) {

  // Y 
  int yc = RGB2Y(r,g,b);
  int uc = RGB2U(r,g,b);
  int vc = RGB2V(r,g,b);
  int j = 0;

  // UV
  int xx = x / 2;
  int yy = y / 2;
  int half_w = gen->width / 2;
  int half_h = gen->height / 2;
  int hh = h / 2;
  int ww = w / 2;

  // y 
  for (j = y; j < (y + h); ++j) {
    memset(gen->y + j * gen->width + x, yc, w);
  }

  // u and v 
  for (j = yy; j < (yy + hh); ++j) {
    memset(gen->u + j * half_w + xx, uc, (ww));
    memset(gen->v + j * half_w + xx, vc, (ww));
  }

  return 0;
}

static int add_number_string(video_generator* gen, const char* str, int x, int y) {

 video_generator_char* found_char = NULL;
 int len = strlen(str);
 int i = 0;
 int k = 0;

 for (i = 0; i < len; ++i) {

   found_char = NULL;

   for (k = 0; k < RXS_MAX_CHARS; ++k) {
     if (gen->chars[k].id == str[i]) {
       found_char = &gen->chars[k];
       break;
     }
   }

   if (!found_char) {
     printf("Error: Cannot find character: %c\n", str[i]);
     continue;
   }

   add_char(gen, found_char, x, y);
   x += found_char->xadvance;
 }

 return 0;
}

static int add_char(video_generator* gen, video_generator_char* kar, int x, int y) {
  int i = 0;
  int j = 0;
  int dest_x = 0;
  int dest_y = 0;
  int src_dx = 0;
  int dest_dx = 0;

  uint8_t* pixels = (uint8_t*)numbersfont_pixel_data; 

  if (!kar) { return -1; } 
  if (!gen) { return -2; } 
  
  for (i = kar->x, dest_x = x; i < (kar->x + kar->width); ++i, ++dest_x) {
    for (j = kar->y, dest_y = y; j < (kar->y + kar->height); ++j, ++dest_y) {
      src_dx = j * gen->font_w + i;
      dest_dx = (kar->yoffset + dest_y) * gen->width + dest_x;
      gen->y[dest_dx] = pixels[src_dx];
    }
  }

  return 0;
}
