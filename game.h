typedef void (*StateRef)();

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
#define ANIM_OFFSET 4
#define ANIM_OFFSET_FEEDBACK (4|8)
#define ANIM_WHITE 16
#define ANIM_BLACK 32

struct AnimHeader {
    uint8_t flags;
    uint8_t frameCount;
    uint8_t frameTime;
};
struct AnimFrameW {
	const uint8_t *white;
};
struct AnimFrameWB {
    const uint8_t *white, *black;
};
struct AnimFrameWBXY {
    const uint8_t *white, *black;
    int8_t x, y;
};

struct Actor;

Actor *drawQueue[ 32 ];
uint8_t queueSize;

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

	Actor &moveTo( uint8_t x, uint8_t y ){
		xH = x;
		xL = 0;
		yH = y;
		yL = 0;
		return *this;
	}

	Actor &setAnimation( const void *_animation ){
		frame = 0;
		currentFrameTime = 0;
		animation = _animation;
		return *this;
	}

	Actor &show(){
		drawQueue[ queueSize++ ] = this;
		return *this;
	}

	Actor &hide(){
		
		for( auto i=queueSize; i; --i ){
			if( drawQueue[i-1] == this ){
				for( ; i<queueSize; ++i )
					drawQueue[i-1] = drawQueue[i];
				queueSize--;
				return *this;
			}
		}
		
		return *this;
	}
};

void flushDrawQueue(){
    
    for( uint8_t i=0; i<queueSize; ++i ){

        Actor &actor = *drawQueue[i];
    
        AnimHeader header;

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
        
        AnimFrameWBXY frame;
		uint8_t sizeofframe = 0;
		if( flags & ANIM_WHITE )
			sizeofframe += sizeof(void *);
		if( flags & ANIM_BLACK )
			sizeofframe += sizeof(void *);
		if( flags & ANIM_OFFSET )
			sizeofframe += 2;

		uint8_t *addr = ((uint8_t *)actor.animation) + sizeof(header) + actor.frame*sizeofframe;

		if( flags & ANIM_WHITE ){
			frame.white = pgm_read_word( addr );
			addr += sizeof(void *);
		}else frame.white = NULL;
		
		if( flags & ANIM_BLACK ){
			frame.black = pgm_read_word( addr );
			addr += sizeof(void *);
		}else frame.black = NULL;
		
		if( flags & ANIM_OFFSET ){
			frame.x = pgm_read_word(addr++);
			frame.y = pgm_read_word(addr);
		}else frame.x = frame.y = 0;

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
    
}


#define STATE( NAME, VARS, INIT, UPDATE )	\
  namespace ns ## NAME { \
    void init();	\
    void update();  \
    struct Type_ ## NAME VARS;   \
  }
#include "states.h"
#undef STATE

enum class State {
  #define STATE( NAME, VAR, INIT, UPDATE ) NAME,
  #include "states.h"
  MAX
} state, prevState = State::MAX;
#undef STATE

#include "global.h"

static union {
  #define STATE( NAME, VAR, INIT, UPDATE ) ns ## NAME :: Type_ ## NAME NAME;
  #include "states.h"  
} stateData;
#undef STATE

const StateRef stateUpdate[] PROGMEM = {
#define STATE( NAME, VAR, INIT, UPDATE ) ns ## NAME :: update,
  #include "states.h"
  NULL
};
#undef STATE

const StateRef stateInit[] PROGMEM = {
#define STATE( NAME, VAR, INIT, UPDATE ) ns ## NAME :: init,
#include "states.h"
  NULL
};
#undef STATE

#define STATE( NAME, VAR, INIT, UPDATE )	\
namespace ns ## NAME {  \
  Type_ ## NAME & scope = ::stateData.NAME;    \
  void init() INIT			\
  void update() UPDATE  \
}
#include "states.h"
#undef STATE

void tick(){
  if (!(arduboy.nextFrame()))
    return;

  pollButtons();

  StateRef func;
  if( state != prevState ){

	queueSize = 0;
    
    func = (StateRef) pgm_read_word( stateInit + uint8_t(state) );
    if( func ) (*func)();
    
    prevState = state;

  }

  func = (StateRef) pgm_read_word( stateUpdate + uint8_t(state) );
  if( func ) (*func)();

  flushDrawQueue();
  
  arduboy.display();
	
}
