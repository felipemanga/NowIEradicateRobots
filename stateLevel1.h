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

	   struct Enemy : public Actor {

	       uint8_t hp;
	       uint8_t timeAlive;
	       uint8_t data;
	       void (*ai)( Enemy * );
	       Actor &init(){
		   Actor::init();
		   hp = 0;
		   timeAlive = 0;
		   ai = NULL;
		   return *this;
	       }		       
		       
	   } enemies[10];

	   uint8_t enemySpawnDelay;
	   uint8_t enemySpawnPattern;
	   uint8_t waveDelay;
		   
       },
       {
	   scope.waveDelay = 100;
	   scope.player.init();
	   for( uint8_t i=0; i<10; ++i )
	       scope.enemies[i].init();
       },
       {
	   if( scope.player.inputEnabled )
	       updatePlayer();
	   
	   if( !scope.waveDelay-- )
	       wave();
	   
	   for( uint8_t i=0; i<10; ++i ){
	       auto &enemy = scope.enemies[i];
	       if( enemy.timeAlive ){
		   (*enemy.ai)( &enemy );
		   enemy.timeAlive++;
		   if( !enemy.hp )
		       enemy.timeAlive = 0;
		   if( !enemy.timeAlive )
		       enemy.hide();
	       }
	   }
       },

       struct Pattern {
	   int8_t startX, startY;
	   int8_t startAngle, angleDelta, radius, radiusDelta;
	   int8_t deltaX, deltaY;
       } const patterns[] PROGMEM = {
	   { 30,30, 0,20,0,10, 0,0 }
       };

       void patternAI( Scope::Enemy *e ){
	   Pattern pattern;
	   pgm_read_struct( &pattern, patterns /*+((t&(t>>3))&3)*sizeof(Pattern)*/ );
	   if( e->timeAlive==1 ){
	       e->data = 0;
	       e->setPosition( pattern.startX, pattern.startY );
	   }

	   if( !e->tweenWeight ){
	       int16_t x, y, a;
	       a = pattern.startAngle;
	       a += int16_t(pattern.angleDelta)*e->data;       
	       x = COS(a) * (
		   int16_t(pattern.radius) +
		   int16_t(pattern.radiusDelta)*e->data
		   ) + int16_t(pattern.deltaX)*e->data;
	       x = (x>>7) + pattern.startX;
	       y = SIN(a) * (
		   int16_t(pattern.radius) +
		   int16_t(pattern.radiusDelta)*e->data
		   ) + int16_t(pattern.deltaY)*e->data;
	       y = (y>>7) + pattern.startY;
	       
	       e->moveTo( x, y );
	       e->data++;
	   }

       }

       void invert();
       
       void wave(){
	   
	   scope.waveDelay = 3*60;
	   uint8_t t = arduboy.frameCount;
	   
	   for( uint8_t i=0; i<10; ++i ){
	       auto &enemy = scope.enemies[i];
	       if( enemy.timeAlive ) continue;
	       t++;
	       invert();	       
	       enemy.ai = patternAI;
	       enemy.timeAlive = 1;
	       enemy.setAnimation( &miniFlightUnit );
	       enemy.hp = 100;
	       enemy.show();
	       return;
	       
	   }
	   
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
	
	
