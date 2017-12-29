#include <Arduboy2.h>

#include "global.h"

#include "states.h"

void setup() {
  arduboy.boot();
  arduboy.setFrameRate(60);
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

  flushDrawQueue();
  
  arduboy.display();

}
