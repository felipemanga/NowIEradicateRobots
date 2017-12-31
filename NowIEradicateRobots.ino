#include <Arduboy2.h>

Arduboy2Base arduboy;

#include "game.h"

void setup() {
  arduboy.boot();
  arduboy.setFrameRate(20);
}

void loop() {
  tick();
}

