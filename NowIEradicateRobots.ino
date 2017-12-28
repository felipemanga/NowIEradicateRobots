#include <Arduboy2.h>

#include "global.h"

#include "states.h"

class _ : public Arduboy2 {
  size_t write(uint8_t c){ return 0; }
} arduboy;

void setup() {
  arduboy.boot();
  arduboy.setFrameRate(8);
  state = State::Init;
  prevState = State::MAX;
}

void loop() {

  if (!(arduboy.nextFrame()))
    return;

  StateRef func;
  if( state != prevState ){
    
    func = (StateRef) pgm_read_word( stateInit + uint8_t(state) );
    if( func ) (*func)();
    
    prevState = state;

  }

  func = (StateRef) pgm_read_word( stateUpdate + uint8_t(state) );
  if( func ) (*func)();

  arduboy.display();

}
