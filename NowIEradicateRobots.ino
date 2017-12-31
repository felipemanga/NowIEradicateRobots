#include <Arduboy2.h>

Arduboy2Base arduboy;

#include "game.h"

void setup() {
  arduboy.boot();
  arduboy.setFrameRate(6);
}

void loop() {
  tick();
}

