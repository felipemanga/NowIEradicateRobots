#include "music.h"

#include "bmp/title.h"

#include "bmp/walk1.h"
#include "bmp/walk2.h"
#include "bmp/walk3.h"
#include "bmp/walk4.h"
#include "bmp/walk5.h"
#include "bmp/walk6.h"
#include "bmp/walk7.h"
#include "bmp/walk8.h"

#include "bmp/tiles.h"

#include "bmp/flightunit.h"
#include "bmp/flightunit2.h"
#include "bmp/minifu1.h"
#include "bmp/minifu2.h"
#include "bmp/enfly1.h"
#include "bmp/enfly2.h"

#include "bmp/shot1.h"
#include "bmp/shot2.h"

struct {
    AnimHeader header;
    AnimFrameWB f;
} const titleAnim PROGMEM = {
    {
	ANIM_WHITE,
	1, 0
    },
    { title_comp_a }
};


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
	AnimFrameWXY f[2];
} const miniFlightUnit PROGMEM = {
	{
		ANIM_WHITE |
		ANIM_PLAY |
		ANIM_LOOP |
		ANIM_OFFSET,
		2, 2,
		16, 16
	},
	{
		{ minifu1_comp_a, -8, -4 },
		{ minifu2_comp_a, -8, -4 }
	}
};

struct {
	AnimHeader header;
	AnimFrameWXY f[2];
} const enFly PROGMEM = {
	{
		ANIM_WHITE |
		ANIM_PLAY |
		ANIM_LOOP |
		ANIM_INVERT |
		ANIM_OFFSET,
		2, 2,
		16, 16
	},
	{
		{ enfly1_comp_a, -8, -4 },
		{ enfly2_comp_a, -8, -4 }
	}
};

struct {
	AnimHeader header;
	AnimFrameWXY f[2];
} const shot PROGMEM = {
    {
	ANIM_WHITE |
	ANIM_INVERT |
	ANIM_OFFSET,
	2, 0,
	8, 8
    },
    {
	{ shot1_comp_a, -4, -4 },
	{ shot2_comp_a, -4, -4 }
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

uint16_t seed, seedSequence;

uint16_t NOISE( uint8_t x, uint8_t y, uint8_t z ){
    return ((SIN( (uint16_t(((y)+seed)/z)*13) + (uint16_t(((x)+seed)/z)*78) )*289&0xFF)*z);
}

int8_t random(int8_t min, int8_t max){
    return (SIN( (arduboy.frameCount*13+(seedSequence++)*79)*seed )*23789&0x3FF>>2 ) % (max-min) + min;
}

uint8_t noise3( uint8_t x, uint8_t y, uint8_t a, uint8_t b ){
    int16_t acc = 0;// 0x80;
    acc += NOISE( x, y, 4 );
    acc += NOISE( x, y, 2 );
    acc += NOISE( x, y, 1 );

    acc >>= 4;

    if( acc > b ) return 2;
    if( acc > a ) return 1;
    return 0;
    
}

uint8_t noise1( uint8_t x, uint8_t y, uint8_t a ){
    int16_t acc = 0;// 0x80;
    acc += NOISE( x, y, 4 );
    acc += NOISE( x, y, 2 );
    acc += NOISE( x, y, 1 );

    acc >>= 4;

    if( acc > a ) return 1;
    return 0;
    
}

typedef uint8_t (*PointCB)( uint8_t x, uint8_t y );

struct TileWindow {
    const unsigned char *tileset;
    uint8_t matrix[81];
    int16_t tx, ty;
    int16_t x, y;
    uint8_t speedX, speedY;
    PointCB point;
    
    void init( const unsigned char * tileset, PointCB p ){
	point = p;
	this->tileset = tileset;
	for( uint8_t i=0; i<81; ++i )
	    matrix[i] = 0xFF;
	tx = ty = x = y = 0;
	speedX = speedY = 0;
    }

    void render( ){
	const uint8_t size = 16;

	int16_t x = this->x + speedX;
	int16_t y = this->y + speedY;
	
	int8_t xL = x % size;
	int8_t yL = y % size;
	int8_t xH = x / size;
	int8_t yH = y / size;

	if( xL >= 0 ){
	    xH--;
	    xL -= size;
	}
	if( yL >= 0 ){
	    yH--;
	    yL -= size;
	}

	int8_t xd = xH - this->tx;
	int8_t yd = this->ty - yH;
	int8_t xs=0, xe=9, xi=1, ys=0, ye=9, yi=1;

	this->tx = xH;
	this->ty = yH;
	this->x = x;
	this->y = y;

	if( xd < -8 || xd > 8 || yd < -8 || yd > 8 )
	    xd = yd = 0;

	if( xd < 0 ){
	    xs = 8;
	    xe = 0;
	    xi = -1;
	}
	xe-=xd;

	if( yd < 0 ){
	    ys = 8;
	    ye = 0;
	    yi = -1;
	}
	ye-=yd;

	auto t = ye;
	ye = ys;
	ys = t;
	yi=-yi;

	if( xd || yd ){	    
	    for( uint8_t ry=ys; ry!=ye; ry+=yi ){
		for( uint8_t rx=xs; rx!=xe; rx+=xi ){
		    matrix[ry*9+rx] = matrix[(ry+yd)*9+rx+xd];
		}
	    }
	}

	if( xd < 0 ){
	    auto t = xs;
	    xs = xe;
	    xe = t;
	}

	{
	    auto t = ye;
	    ye = ys;
	    ys = t;
	}	    
	
	for( uint8_t ry=0; ry<9; ++ry ){
	    uint8_t miss = ry < ys || ry >= ye;
	    
	    for( uint8_t rx=0; rx<9; ++rx ){
		uint8_t i = ry*9+rx;
		uint8_t tile = matrix[i];
		
		if( miss || rx < xs || rx >= xe || tile == 0xFF )
		    tile = matrix[i] = point(rx-xH, ry-yH);
		// else tile = 0xFF;

		if( tile != 0xFF ){
		    Sprites::drawBitmap(
			rx*size+xL,
			ry*size+yL,
			// (const uint8_tp) pgm_read_word( tileset+tile ),
			tileset+tile*32,
			NULL,
			16,16,
			2
			);
		}
		
	    }
	}
    }
};

struct LiveActor : public Actor {
    uint8_t hp;
    uint8_t immune;
    
    void (*onDamage)( LiveActor *actor );
    
    void damage( uint8_t amt ){
	if( !amt || !hp || immune ) return;
	if( amt > hp )
	    amt = hp;
	hp -= amt;
	immune = 10;
	flags |= ANIM_GRAY;
	(*onDamage)( this );
    }

    void update(){
	if( immune ){
	    immune--;
	    if( !immune )
		flags &= ~ANIM_GRAY;
	}
    }
};

struct Shot : public Actor {
    int8_t dx, dy, ttl;

    Actor *search;
    uint8_t searchCount;
    uint8_t searchSize;
    
    Actor &init( Actor &shooter, Actor *search, uint8_t searchCount, uint8_t searchSize ){
	ttl = 60;
	this->search = search;
	this->searchCount = searchCount;
	this->searchSize = searchSize;
	Actor::init()
	    .setAnimation( &shot );
	
	x = shooter.x;
	y = shooter.y;
	flags |= ANIM_INVERT;
	actorFlags &= ~ACTOR_HIDDEN;
	
	return *this;
    }
};

void updateShots( Shot *shots, uint8_t count ){
    for( uint8_t i=0; i<count; ++i ){
	Shot &shot = shots[i];
	if( shot.ttl ){
	    
	    shot.xH += shot.dx;
	    shot.yH += shot.dy;

	    shot.ttl--;
	    
	    shot.checkCollision(
		shot.search,
		shot.searchSize,
		shot.searchCount,
		[]( Actor *target ){
		    ((LiveActor *)target)->damage(20);
		}
		);
	    
	    if( !shot.ttl )
		shot.actorFlags |= ACTOR_HIDDEN;


	}
    }
}

Shot *allocShot( Shot *shots, uint8_t count ){
    for( uint8_t i=0; i<count; ++i ){
	Shot &shot = shots[i];
	if( !shot.ttl )
	    return &shot;
    }
    return NULL;
}

#define MAX_SHOT_COUNT 15

struct Enemy : public LiveActor {

    uint8_t timeAlive;
    uint8_t id;
    void *data;
    void (*ai)( Enemy * );
    void (*shoot)( Enemy * );
    
    Actor &init(){
	Actor::init();
	hp = 0;
	timeAlive = 0;
	ai = NULL;
	return *this;
    }		       

    void destroy(){
	actorFlags |= ACTOR_HIDDEN;
	timeAlive = 0;
    }
};

#define MAX_ENEMY_COUNT 9

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
	    enemy.init();
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
	    if( enemy.shoot && (enemy.timeAlive+i*167)%128==0 )
		(*enemy.shoot)( &enemy );
	    
	    if( !enemy.hp )
		enemy.timeAlive = 0;
	    if( !enemy.timeAlive )
		enemy.destroy();
	}
    }

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
	205,0xFF,
	100,10,0,
	0,0,0
    },
    { // Coil Top Left 3
	0,0,
	0,5,
	10,10,0,
	17,5,0
    },
    { // Coil Top Right 4
	127,0,
	0,5,
	10,10,0,
	-17,5,0
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
    },
    { // O Top 9
	64,-10,
	0,1,
	60,50,0,
	0,0,0
    },
    { // O Top2 10
	64,-10,
	128,0xFF,
	40,40,0,
	0,0,0
    },
    { // O Bottom 11
	64,64,
	0,0xFF,
	50,50,0,
	0,0,0
    },
    { // ZigZag big 12
	64,-15, 
	0,1,
	70,0,0,
	0,3,2 
    },
    { // v-line 13
	64,-15, 
	0,0,
	0,0,0,
	0,15,0 
    }
    
};

#include "flightMode.h"
