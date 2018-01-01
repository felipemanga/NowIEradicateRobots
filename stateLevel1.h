STATE( Level1,
       {
	   struct Player : public Actor {
			   
	       bool inputEnabled;
	       int8_t accX;
	       int8_t accY;
	       int16_t speedX;
	       int16_t speedY;
	       Actor &init();
			   
	   } player;

	   Enemy enemies[10];

	   Wave wave;
		   
       },
       {
	   scope.player.init();
	   scope.wave.init(
	       50,
	       20,
	       5,
	       spawnEnemy
	       );
	   for( uint8_t i=0; i<10; ++i )
	       scope.enemies[i].init();
       },
       {
	   if( scope.player.inputEnabled )
	       updatePlayer();

	   scope.wave.update( scope.enemies, 10 );
	   updateEnemies( scope.enemies, 10 );
	   
       },

       const uint8_t sequence[] PROGMEM = {
	   5,
	       6,
	       7,
	       8,
	       5,
	       6,
	       1,
	       2,
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
	   enemy.setAnimation( &miniFlightUnit );
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
		   
	   player.speedY += player.accY * 20;
	   if( player.speedY > 500 )
	       player.speedY = 500;
	   if( player.speedY < -500 )
	       player.speedY = -500;
		   
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
	
	
