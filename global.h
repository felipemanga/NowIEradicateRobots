#include "bmp/av1.h"
#include "bmp/hair2.h"
#include "bmp/base1.h"
#include "bmp/bg1.h"
#include "bmp/walk1.h"
#include "bmp/walk2.h"
#include "bmp/walk3.h"
#include "bmp/walk4.h"
#include "bmp/walk5.h"
#include "bmp/walk6.h"
#include "bmp/walk7.h"
#include "bmp/walk8.h"

Arduboy2Base arduboy;

const uint8_t * const walk[] PROGMEM = {
    walk1_comp_w, walk1_comp_b, 
    walk2_comp_w, walk2_comp_b,
    walk3_comp_w, walk3_comp_b,
    walk4_comp_w, walk4_comp_b,
    walk5_comp_w, walk5_comp_b,
    walk6_comp_w, walk6_comp_b,
    walk7_comp_w, walk7_comp_b,
    walk8_comp_w, walk8_comp_b
};

const int8_t PROGMEM offset[] = {
    0, 1,
    3, 0,
    4, -1,
    9, 0,
    0, 1,
    3, -1,
    4, 0,
    9, 0
};
