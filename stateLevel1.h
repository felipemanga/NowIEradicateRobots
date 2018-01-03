STATE( Level1,
       {
	   struct Player : public ActorBBox {
			   
	       bool inputEnabled;
	       int8_t accX;
	       int8_t accY;
	       int16_t speedX;
	       int16_t speedY;
	       Actor &init();
			   
	   } player;

	   Enemy enemies[MAX_ENEMY_COUNT];

	   Shot shots[MAX_SHOT_COUNT];

	   Wave wave;

	   TileWindow ground;

	   uint16_t groundX;
	   uint16_t groundY;
		   
       },
       {
	   playChiptune([](uint16_t t){
		   return t>>3|t>>6|t;
	       }, false);
	   
	   seed = 0xBEEF;
	   seedSequence = 0;
	   
	   scope.groundX = 0;
	   scope.groundY = 0;
	   
	   scope.ground.init(
	       (void**) tileset,
	       16,
	       [](uint8_t x, uint8_t y)->uint8_t{
		   int16_t acc = 0;
		   acc += NOISE( x, y, 3 );
		   acc += NOISE( x, y, 2 );
		   acc += NOISE( x, y, 1 );
		   
		   return 0; //acc>>4;
	       });
	   scope.ground.x = 0;
	   scope.ground.y = 0;
	   
	   scope.player.init();
	   scope.wave.init(
	       50,
	       20,
	       5,
	       spawnEnemy
	       );
	   for( uint8_t i=0; i<MAX_ENEMY_COUNT; ++i )
	       scope.enemies[i].init();
       },
       {
	   if( scope.player.inputEnabled )
	       updatePlayer();

	   scope.ground.render( scope.groundX, scope.groundY+=8 );

	   scope.wave.update( scope.enemies, MAX_ENEMY_COUNT );
	   updateEnemies( scope.enemies, MAX_ENEMY_COUNT );
	   updateShots( scope.shots, MAX_SHOT_COUNT );
	   
       },

       const void * const tileset[] PROGMEM = {
	   tiles1
       };

       const uint8_t sequence[] PROGMEM = {
	   13,
	   5,
	       6,
	       7,
	       8,
	       
	       5,
	       6,
	       1,
	       2,
	       12,
	       
	       6,
	       5,
	       3,
	       4,
	       
	       10,
	       9,
	       2,
	       1,
	       8,
	       12,
	       
	       0,
	       0
       };
              
       void invert();
              
       bool spawnEnemy( Enemy &enemy, uint8_t eid, uint8_t wid ){
	   if( !pgm_read_byte(sequence + wid + 1) )
	       scope.wave.waveDelay = 200;
	   
	   wid = pgm_read_byte(sequence + wid);
	   if( wid )
	       wid--;
	   else if( scope.player.inputEnabled ){
	       scope.player
		   .moveTo( scope.player.xH, -40 )
		   .setTweenWeight( 5 )
		   .onTweenComplete([]{
			   state = State::Init;
		       });
	       scope.player.inputEnabled = false;
	       return false;
	   }else return false;
	   
	   enemy.data = (void *) (patterns+wid);
	   enemy.ai = patternAI;	   
	   enemy.timeAlive = 1;
	   enemy.setAnimation( &enFly );
	   enemy.hp = 100;
	   
	   return true;
       }
       
       void invert(){
	   scope.player.flags ^= ANIM_INVERT;
	   clearScreen ^= 1;
       }       

       Actor &Scope::Player::init(){
	   Actor::init()
	       .setPosition( 64, 128+16 )
	       .moveTo( 64, 32 )
	       .setTweenWeight( 4 )
	       .setAnimation( &miniFlightUnit )
	       .onTweenComplete([]{
		       scope.player.inputEnabled = true;
		   })
	       .show()
	       ;
	   flags |= ANIM_INVERT;
	   inputEnabled = false;
	   accX = 0;
	   accY = 0;
	   speedX = 0;
	   speedY = 0;
	   return *this;
       }
	   

       void updatePlayer(){
	   auto &player = scope.player;

	   if( justPressed(B_BUTTON) )
	       invert();
		   
	   if( isPressed(LEFT_BUTTON) )
	       player.accX = -1;
	   else if( isPressed(RIGHT_BUTTON) )
	       player.accX = 1;
	   else if( player.speedX > 0 )
	       player.accX = -1;
	   else if( player.speedX < 0 )
	       player.accX = 1;
	   else
	       player.accX = 0;
		   
	   player.speedX += player.accX * 25;
	   if( player.speedX > 500 )
	       player.speedX = 500;
	   if( player.speedX < -500 )
	       player.speedX = -500;
		   
	   if( (scope.player.xH < 0 && player.speedX < 0) || (player.speedX > 0 && (scope.player.x+player.speedX<scope.player.x)) )
	       player.speedX = 0;
		   
	   scope.player.x += player.speedX;

	   if( isPressed(UP_BUTTON) )
	       player.accY = -1;
	   else if( isPressed(DOWN_BUTTON) )
	       player.accY = 1;
	   else if( player.speedY > 0 )
	       player.accY = -1;
	   else if( player.speedY < 0 )
	       player.accY = 1;
	   else
	       player.accY = 0;
		   
	   player.speedY += player.accY * 30;
	   if( player.speedY > 700 )
	       player.speedY = 700;
	   if( player.speedY < -700 )
	       player.speedY = -700;
		   
	   if(
	       (scope.player.yH < 0 && player.speedY < 0) ||
	       (player.speedY > 0 &&
		(scope.player.y+player.speedY>0x3C00)
		   )
	       )
	       player.speedY = 0;
		   
	   scope.player.y += player.speedY;
		   
       }
	   
    )
	
	
