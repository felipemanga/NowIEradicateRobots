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

#include "bmp/flightunit.h"
#include "bmp/flightunit2.h"
#include "bmp/minifu1.h"
#include "bmp/minifu2.h"


struct {
	AnimHeader header;
	AnimFrameWBXY a, b;
} const flightUnitFly PROGMEM = {
	{
		ANIM_WHITE |
		ANIM_BLACK |
		ANIM_INVERT |
		ANIM_LOOP |
		ANIM_OFFSET,
		2, 1
	},
	{
		flightunit_comp_a,
		flightunit_comp_w,
		-16, -16
	},
	{
		flightunit2_comp_a,
		flightunit_comp_w,
		-16, -16
	}
};

struct {
	AnimHeader header;
	AnimFrameWBXY f[2];
} const miniFlightUnit PROGMEM = {
	{
		ANIM_WHITE |
		ANIM_BLACK |
		ANIM_PLAY |
		ANIM_LOOP |
		ANIM_OFFSET,
		2, 2
	},
	{
		{ minifu1_comp_a, minifu1_comp_w, -8, -4 },
		{ minifu2_comp_a, minifu2_comp_w, -8, -4 }
	}
};

struct {
    AnimHeader header;
    AnimFrameWBXY f[8];
} const girlWalk PROGMEM = {
    {
		ANIM_WHITE |
		ANIM_BLACK |
		ANIM_OFFSET_FEEDBACK |
		ANIM_LOOP,
		8, // frame count
		8 // each animation frame is N game frames
	},
    {
        { walk1_comp_w, walk1_comp_b, 0,  1 },
        { walk2_comp_w, walk2_comp_b, 3,  0 },
        { walk3_comp_w, walk3_comp_b, 4, -1 },
        { walk4_comp_w, walk4_comp_b, 9,  0 },
        { walk5_comp_w, walk5_comp_b, 0,  1 },
        { walk6_comp_w, walk6_comp_b, 3, -1 },
        { walk7_comp_w, walk7_comp_b, 4,  0 },
        { walk8_comp_w, walk8_comp_b, 9,  0 }
    }
};

const int8_t PROGMEM sincos[] = {
0,3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,48,51,54,57,59,62,65,67,70,73,75,78,80,82,85,87,89,91,94,96,98,100,102,103,105,107,108,110,112,113,114,116,117,118,119,120,121,122,123,123,124,125,125,126,126,126,126,126,127,126,126,126,126,126,125,125,124,123,123,122,121,120,119,118,117,116,114,113,112,110,108,107,105,103,102,100,98,96,94,91,89,87,85,82,80,78,75,73,70,67,65,62,59,57,54,51,48,45,42,39,36,33,30,27,24,21,18,15,12,9,6,3,0,-3,-6,-9,-12,-15,-18,-21,-24,-27,-30,-33,-36,-39,-42,-45,-48,-51,-54,-57,-59,-62,-65,-67,-70,-73,-75,-78,-80,-82,-85,-87,-89,-91,-94,-96,-98,-100,-102,-103,-105,-107,-108,-110,-112,-113,-114,-116,-117,-118,-119,-120,-121,-122,-123,-123,-124,-125,-125,-126,-126,-126,-126,-126,-127,-126,-126,-126,-126,-126,-125,-125,-124,-123,-123,-122,-121,-120,-119,-118,-117,-116,-114,-113,-112,-110,-108,-107,-105,-103,-102,-100,-98,-96,-94,-91,-89,-87,-85,-82,-80,-78,-75,-73,-70,-67,-65,-62,-59,-57,-54,-51,-48,-45,-42,-39,-36,-33,-30,-27,-24,-21,-18,-15,-12,-9,-6,-3
};

inline int8_t SIN( int16_t x){
    if( x < 0 )
        x = 256-x;
    return pgm_read_byte(sincos+(x&0xFF));
}

inline int8_t COS( int16_t x ){
    return SIN(x+180);
}


struct Enemy : public Actor {

    uint8_t hp;
    uint8_t timeAlive;
    void *data;
    void (*ai)( Enemy * );
    Actor &init(){
	Actor::init();
	hp = 0;
	timeAlive = 0;
	ai = NULL;
	return *this;
    }		       
    
};

struct Pattern {
    int8_t startX, startY;
    uint8_t startAngle, angleDelta;
    int8_t radiusX, radiusY,
	radiusDelta;
    int8_t deltaX, deltaY, tweenWeight;
};

void patternAI( Enemy *e ){
    Pattern pattern;

    if( e->tweenWeight )
	return;

    uint8_t time = e->timeAlive;
    
    pgm_read_struct( &pattern, (const uint8_t *) e->data );

    int16_t x, y, a;
    a = pattern.startAngle;
    a += int16_t(pattern.angleDelta)*time;
	       
    x = COS(a) * (
	int16_t(pattern.radiusX)*2 +
	int16_t(pattern.radiusDelta)*time
	);
    x += (int16_t(pattern.deltaX)*time*16);
    x >>= 8;
    x += pattern.startX;

    y = SIN(a) * (
	int16_t(pattern.radiusY)*2 +
	int16_t(pattern.radiusDelta)*time
	);
    y += (int16_t(pattern.deltaY)*time*16);
    y >>= 8;
    y += pattern.startY;
    
    if( pattern.tweenWeight && time > 1 ){
	e->moveTo( x, y )
	    .setTweenWeight( pattern.tweenWeight );
    }else{
	e->setPosition( x, y );
    }

}

typedef bool (*SpawnCallback)(
    Enemy &,
    uint8_t enemyId,
    uint8_t waveId
    );

struct Wave {
    uint8_t enemySpawnDelay, defaultEnemySpawnDelay;
    uint8_t enemySpawnCount, defaultEnemySpawnCount;
    uint8_t waveDelay, defaultWaveDelay, id;
    SpawnCallback onSpawn;
    void update( Enemy *enemies, uint8_t maxEnemies );
    void init(
	uint8_t waveDelay,
	uint8_t spawnDelay,
	uint8_t spawnCount,
	SpawnCallback onSpawn
    );
};

void Wave::init(
    uint8_t waveDelay,
    uint8_t spawnDelay,
    uint8_t spawnCount,
    SpawnCallback onSpawn
    ){
    id = 0xFF;
    this->waveDelay = defaultWaveDelay = waveDelay;
    enemySpawnDelay = 0; defaultEnemySpawnDelay = spawnDelay;
    enemySpawnCount = 0; defaultEnemySpawnCount = spawnCount;
    this->onSpawn = onSpawn;
}
    
void Wave::update( Enemy *enemies, uint8_t maxEnemies ){
    waveDelay -= arduboy.frameCount & 1;
    if( waveDelay ){

	if( !enemySpawnCount || enemySpawnDelay-- ) return;
	
	enemySpawnDelay = defaultEnemySpawnDelay;
	
	for( uint8_t i=0; i<maxEnemies; ++i ){
	    auto &enemy = enemies[i];
	    if( enemy.timeAlive ) continue;
	    
	    enemySpawnCount--;
	    if( !(*onSpawn)(
		    enemy,
		    defaultEnemySpawnCount-enemySpawnCount,
		    id
		    )
		)
		return;
	    
	    enemy.show();

	    break;
	       
	}
	
    }else{
	
	id++;
	waveDelay = 4*30;
	enemySpawnCount = defaultEnemySpawnCount;
	enemySpawnDelay = 0;
	
    }	   
	   
}

void updateEnemies( Enemy *enemies, uint8_t maxEnemies ){
    
    for( uint8_t i=0; i<maxEnemies; ++i ){
	auto &enemy = enemies[i];
	if( enemy.timeAlive ){
	    (*enemy.ai)( &enemy );
	    enemy.timeAlive++;
	    if( !enemy.hp )
		enemy.timeAlive = 0;
	    if( !enemy.timeAlive )
		enemy.hide();
	}
    }

}

uint8_t tune( uint16_t t ){
    return (t>>7|t|t>>6)*10+(t&t>>13|t>>6)*4;
}


/*
  startX startY
  startAngle angleDelta
  radiusX radiusY radiusDelta
  deltaX, deltaY, tweenWeight;
*/
       
const Pattern patterns[] PROGMEM = {
    { // O Right 1
	127,22,
	127,1,
	100,10,0,
	0,0,0
    },
    { // O Left 2
	0,22,
	0,0xFF,
	100,10,0,
	0,0,0
    },
    { // Coil Top Left 3
	0,0,
	0,10,
	5,5,0,
	13,5,0
    },
    { // Coil Top Right 4
	127,0,
	0,10,
	5,5,0,
	-13,5,0
    },
    { // Mosquito Top Right 5
	127, 16,
	0,180,
	0,15,0,
	-15,0,2	       
    },	   
    { // Mosquito Mid Left 6
	0, 32,
	0,180,
	0,15,0,
	15,0,2	       
    },	   
    { // ZigZag Left 7
	30,-15, 
	0,5,
	15,0,0,
	0,10,
	0 
    },
    { // ZigZag Right 8
	128-30,-15, 
	0,255-5,
	15,0,0,
	0,10,
	0
    }
};
