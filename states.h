#ifdef STATES_H
  #ifdef STATE
    #include "stateInit.h"
    #undef STATE
  #endif
#else

#define STATES_H

typedef void (*StateRef)();

#define STATE( NAME, VARS, INIT, UPDATE )	\
  namespace ns ## NAME { \
    void init();	\
    void update();  \
    struct Type_ ## NAME VARS;   \
  }
#include "states.h"

static union {
  #define STATE( NAME, VAR, INIT, UPDATE ) ns ## NAME :: Type_ ## NAME NAME;
  #include "states.h"  
} stateData;

enum class State {
  #define STATE( NAME, VAR, INIT, UPDATE ) NAME,
  #include "states.h"
  MAX
} state, prevState;

const StateRef stateUpdate[] PROGMEM = {
#define STATE( NAME, VAR, INIT, UPDATE ) ns ## NAME :: update,
  #include "states.h"
  NULL
};

const StateRef stateInit[] PROGMEM = {
#define STATE( NAME, VAR, INIT, UPDATE ) ns ## NAME :: init,
#include "states.h"
  NULL
};

#define STATE( NAME, VAR, INIT, UPDATE )	\
namespace ns ## NAME {  \
  Type_ ## NAME & scope = ::stateData.NAME;    \
  void init() INIT			\
  void update() UPDATE  \
}
#include "states.h"

#endif
