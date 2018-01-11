#include <Arduboy2.h>

Arduboy2Base arduboy;

#include "game.h"

void setup() {
  arduboy.boot();
  arduboy.flashlight();
  arduboy.setFrameRate(60);
}

void loop() {
  tick();
}

