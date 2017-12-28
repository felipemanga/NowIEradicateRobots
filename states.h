#ifdef STATES_H
  #ifdef STATE
    #include "stateInit.h"
    #undef STATE
  #endif
#else

#define STATES_H

typedef void (*StateRef)();

#define STATE( NAME, VARS, INIT, UPDATE )	\
  void init ## NAME ();				\
  void update ## NAME ();
#include "states.h"

static union {
  #define STATE( NAME, VAR, INIT, UPDATE ) struct VAR NAME;
  #include "states.h"  
};

enum class State {
  #define STATE( NAME, VAR, INIT, UPDATE ) NAME,
  #include "states.h"
  MAX
} state, prevState;

const StateRef stateUpdate[] PROGMEM = {
#define STATE( NAME, VAR, INIT, UPDATE ) update ## NAME,
  #include "states.h"
  NULL
};

const StateRef stateInit[] PROGMEM = {
#define STATE( NAME, VAR, INIT, UPDATE ) init ## NAME,
#include "states.h"
  NULL
};

#define STATE( NAME, VAR, INIT, UPDATE )	\
  void init ## NAME () INIT			\
  void update ## NAME () UPDATE
#include "states.h"

#endif
