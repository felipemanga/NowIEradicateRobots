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

uint8_t previousButtonState, currentButtonState, _justPressed;
#define justPressed( x ) (_justPressed&(x))
void pollButtons(){
    previousButtonState = currentButtonState;
    currentButtonState = arduboy.buttonsState();
    _justPressed = (previousButtonState^currentButtonState)&currentButtonState;
}


typedef uint8_t *uint8_tp;
typedef uint16_t *uint16_tp;
typedef uint32_t *uint32_tp;

template <int S> void memcpy_Pn( void *out, const uint8_t *src ){
    memcpy_P( out, src, S );
}
template <> void memcpy_Pn <1> ( void *out, const uint8_t *src ){
    *uint8_tp(out) = pgm_read_byte(src);
}
template <> void memcpy_Pn <2> ( void *out, const uint8_t *src ){
    *uint16_tp(out) = pgm_read_word(src);
}
template <> void memcpy_Pn <3> ( void *out, const uint8_t *src ){
    *uint16_tp(out) = pgm_read_word(src);
    *(uint8_tp(out)+2) = pgm_read_byte(src+2);
}
template <> void memcpy_Pn <4> ( void *out, const uint8_t *src ){
    *uint32_tp(out) = pgm_read_dword(src);
}
template <> void memcpy_Pn <5> ( void *out, const uint8_t *src ){
    *uint32_tp(out) = pgm_read_dword(src);
    *(uint8_tp(out)+4) = pgm_read_byte(src+4);
}
template <> void memcpy_Pn <6> ( void *out, const uint8_t *src ){
    *uint32_tp(out) = pgm_read_dword(src);
    *(uint16_tp(out)+2) = pgm_read_word(src+4);
}
template <> void memcpy_Pn <7> ( void *out, const uint8_t *src ){
    *uint32_tp(out) = pgm_read_dword(src);
    *(uint16_tp(out)+2) = pgm_read_word(src+4);
    *(uint8_tp(out)+6) = pgm_read_byte(src+6);
}
template <> void memcpy_Pn <8> ( void *out, const uint8_t *src ){
    *uint32_tp(out) = pgm_read_dword(src);
    *(uint32_tp(out)+1) = pgm_read_dword(src+4);
}

template <typename T> void pgm_read_struct( T *header, const void *src ){
    memcpy_Pn<sizeof(T)>( header, (const uint8_t *) src );
}
#define ANIM_PLAY 1
#define ANIM_LOOP 2
#define ANIM_OFFSET_FEEDBACK 4

struct AnimationHeader {
    uint8_t flags;
    uint8_t frameCount;
    uint8_t frameTime;
};

struct AnimationFrame {
    int8_t x, y;
    const uint8_t *white, *black;
};

struct Actor {
    union{
        int16_t x;
        struct {
            int8_t xH;
            uint8_t xL;
        };
    };
    union{
        int16_t y;
        struct {
            int8_t yH;
            uint8_t yL;
        };
    };
    uint8_t frame, currentFrameTime, flags;
    const void *animation;
};

Actor *drawQueue[ 32 ];
uint8_t queueSize;

void draw( Actor &actor ){
    drawQueue[queueSize++] = &actor;
}

void flushDrawQueue(){
    
    for( uint8_t i=0; i<queueSize; ++i ){

        Actor &actor = *drawQueue[i];
    
        AnimationHeader header;

        pgm_read_struct( &header, actor.animation );
        
        uint8_t flags = actor.flags | header.flags;

        if( flags & ANIM_PLAY ){
            actor.currentFrameTime++;
            if( actor.currentFrameTime >= header.frameTime ){
                actor.frame++;
                actor.currentFrameTime = 0;
            }
        }

        if( actor.frame >= header.frameCount ){
            if( flags & ANIM_LOOP ) actor.frame = 0;
            else actor.frame = header.frameCount - 1;
        }
        
        AnimationFrame frame;
        pgm_read_struct( &frame, ((uint8_t *)actor.animation) + sizeof(header) + actor.frame*sizeof(frame) );


        int8_t x;
        int8_t y;

        if( (flags & (ANIM_OFFSET_FEEDBACK | ANIM_PLAY)) == (ANIM_OFFSET_FEEDBACK | ANIM_PLAY) ){
            if( !actor.currentFrameTime ){
                actor.xH += frame.x;
                actor.yH += frame.y;
            }
            x = actor.xH;
            y = actor.yH;
        }else{
            x = actor.xH + frame.x;
            y = actor.yH + frame.y;
        }

        if( frame.white )
            arduboy.drawCompressed( x, y, frame.white );
            
        if( frame.black )
            arduboy.drawCompressed( x, y, frame.black, 0 );
        
    
    }
    
    queueSize = 0;
    
}

struct {
    AnimationHeader header;
    AnimationFrame f[8];
} const girlWalk PROGMEM = {
    { ANIM_LOOP | ANIM_OFFSET_FEEDBACK, 8, 7 },
    {
        { 0, 1, walk1_comp_w, walk1_comp_b },
        { 3, 0, walk2_comp_w, walk2_comp_b },
        { 4,-1, walk3_comp_w, walk3_comp_b },
        { 9, 0, walk4_comp_w, walk4_comp_b },
        { 0, 1, walk5_comp_w, walk5_comp_b },
        { 3,-1, walk6_comp_w, walk6_comp_b },
        { 4, 0, walk7_comp_w, walk7_comp_b },
        { 9, 0, walk8_comp_w, walk8_comp_b }
    }
};
/*
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
*/
