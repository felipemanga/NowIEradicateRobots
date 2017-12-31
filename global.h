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

#include "bmp/flightunit.h"
#include "bmp/flightunit2.h"
#include "bmp/minifu1.h"
#include "bmp/minifu2.h"


struct {
	AnimHeader header;
	AnimFrameWBXY a, b;
} const flightUnitFly PROGMEM = {
	{
		ANIM_WHITE |
		ANIM_BLACK |
		ANIM_INVERT |
		ANIM_LOOP |
		ANIM_OFFSET,
		2, 1
	},
	{
		flightunit_comp_a,
		flightunit_comp_w,
		-16, -16
	},
	{
		flightunit2_comp_a,
		flightunit_comp_w,
		-16, -16
	}
};

struct {
	AnimHeader header;
	AnimFrameWBXY f[2];
} const miniFlightUnit PROGMEM = {
	{
		ANIM_WHITE |
		ANIM_BLACK |
		ANIM_PLAY |
		ANIM_LOOP |
		ANIM_OFFSET,
		2, 2
	},
	{
		{ minifu1_comp_a, minifu1_comp_w, -8, -4 },
		{ minifu2_comp_a, minifu2_comp_w, -8, -4 }
	}
};

struct {
    AnimHeader header;
    AnimFrameWBXY f[8];
} const girlWalk PROGMEM = {
    {
		ANIM_WHITE |
		ANIM_BLACK |
		ANIM_OFFSET_FEEDBACK |
		ANIM_LOOP,
		8, // frame count
		8 // each animation frame is N game frames
	},
    {
        { walk1_comp_w, walk1_comp_b, 0,  1 },
        { walk2_comp_w, walk2_comp_b, 3,  0 },
        { walk3_comp_w, walk3_comp_b, 4, -1 },
        { walk4_comp_w, walk4_comp_b, 9,  0 },
        { walk5_comp_w, walk5_comp_b, 0,  1 },
        { walk6_comp_w, walk6_comp_b, 3, -1 },
        { walk7_comp_w, walk7_comp_b, 4,  0 },
        { walk8_comp_w, walk8_comp_b, 9,  0 }
    }
};

const int8_t PROGMEM sincos[] = {
0,3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,48,51,54,57,59,62,65,67,70,73,75,78,80,82,85,87,89,91,94,96,98,100,102,103,105,107,108,110,112,113,114,116,117,118,119,120,121,122,123,123,124,125,125,126,126,126,126,126,127,126,126,126,126,126,125,125,124,123,123,122,121,120,119,118,117,116,114,113,112,110,108,107,105,103,102,100,98,96,94,91,89,87,85,82,80,78,75,73,70,67,65,62,59,57,54,51,48,45,42,39,36,33,30,27,24,21,18,15,12,9,6,3,0,-3,-6,-9,-12,-15,-18,-21,-24,-27,-30,-33,-36,-39,-42,-45,-48,-51,-54,-57,-59,-62,-65,-67,-70,-73,-75,-78,-80,-82,-85,-87,-89,-91,-94,-96,-98,-100,-102,-103,-105,-107,-108,-110,-112,-113,-114,-116,-117,-118,-119,-120,-121,-122,-123,-123,-124,-125,-125,-126,-126,-126,-126,-126,-127,-126,-126,-126,-126,-126,-125,-125,-124,-123,-123,-122,-121,-120,-119,-118,-117,-116,-114,-113,-112,-110,-108,-107,-105,-103,-102,-100,-98,-96,-94,-91,-89,-87,-85,-82,-80,-78,-75,-73,-70,-67,-65,-62,-59,-57,-54,-51,-48,-45,-42,-39,-36,-33,-30,-27,-24,-21,-18,-15,-12,-9,-6,-3
};

inline int8_t SIN( int16_t x){
    if( x < 0 )
        x = 256-x;
    return pgm_read_byte(sincos+(x&0xFF));
}

inline int8_t COS( int16_t x ){
    return SIN(x+180);
}
