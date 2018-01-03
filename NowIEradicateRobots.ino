#include <Arduboy2.h>

Arduboy2Base arduboy;

#include "game.h"

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);
}

void loop() {
  tick();
}

