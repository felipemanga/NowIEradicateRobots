/*
Hello, World! example
June 11, 2015
Copyright (C) 2015 David Martinez
All rights reserved.
This code is the most basic barebones code for writing a program for Arduboy.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
*/

#include <Arduboy2.h>
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

// make an instance of arduboy used for many functions
Arduboy2 arduboy;

void setup() {
  // initiate arduboy instance
  arduboy.boot();

  // here we set the framerate to 15, we do not need to run at
  // default 60 and it saves us battery life
  arduboy.setFrameRate(8);
}

uint8_t frame;
int16_t x = -20, y = 16;

// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop() {
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  
  for( uint8_t i=0; i<128/4; ++i ){
    Sprites::drawOverwrite( i*4, 0, bg1, 0 );
  }
  x += (int8_t) pgm_read_byte( offset+frame*2 );
  y += (int8_t) pgm_read_byte( offset+frame*2+1 );
  if( x > 128 ) x = -20;
  
  arduboy.drawCompressed( x, y, pgm_read_word(walk+frame*2) );
  arduboy.drawCompressed( x, y, pgm_read_word(walk+frame*2+1), 0 );

  frame = (frame+1) % 8;
  

  // Sprites::drawExternalMask( 0, 0, av1, av1_mask, 0, 0 ); // av1+av1_mask = 2050b. 19360b free

  // then we finaly we tell the arduboy to display what we just wrote to the display
  arduboy.display();
}
