STATE( Level1,
       {
	   FlightModePlayer player;

	   Enemy enemies[MAX_ENEMY_COUNT];

	   Shot shots[MAX_SHOT_COUNT];

	   Wave wave;

	   TileWindow ground;

       },
       {
	   playChiptune([](uint16_t t){
		   return t>>3|t>>6|t&0x7;
	       });
	   
	   seed = 0x1942;
	   seedSequence = 0;
	   scope.ground.init( tiles, flightModeGroundGen );
	   scope.ground.speedY = 1;
	   
	   scope.player.init()
	       .setPosition( 64, 128+16 )
	       .moveTo( 64, 32 )
	       .setTweenWeight( 4 )
	       .onTweenComplete([]{
		   scope.player.inputEnabled = true;
	       });
	   scope.player.onDamage = playerDamage;
	   
	   scope.wave.init( 50, 20, 5, spawnEnemy );
	   
	   for( uint8_t i=0; i<MAX_ENEMY_COUNT; ++i )
	       scope.enemies[i].timeAlive = 0;
	   
	   for( uint8_t i=0; i<MAX_SHOT_COUNT; ++i ){
	       Shot &shot = scope.shots[i];
	       shot.show();
	       shot.ttl = 0;
	       shot.actorFlags = ACTOR_HIDDEN;
	   }
	   
       },
       {
	   if( !scope.player.immune )
	       checkCollisions();

	   scope.ground.render();
	   scope.player.update();
	   scope.wave.update( scope.enemies, MAX_ENEMY_COUNT );
	   updateEnemies( scope.enemies, MAX_ENEMY_COUNT );
	   updateShots( scope.shots, MAX_SHOT_COUNT );
	   
       },

       void checkCollisions(){
	   scope.player.checkCollision(
	       scope.enemies,
	       MAX_ENEMY_COUNT,
	       []( Actor *a ){
		   auto e = (Enemy *) a;
		   if( e->timeAlive <= 1 || scope.player.immune )
		       return;
		   e->destroy();
		   scope.player.damage( 10 );
	       }
	       );
       }

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

       void playerDamage( LiveActor *actor ){
	   actor->immune = 60;
	   if( actor->hp ) return;
	   FlightModePlayer *player = (FlightModePlayer *) actor;
	   player->inputEnabled = false;
	   actor->actorFlags |= ACTOR_HIDDEN;
	   actor->setPosition(0,0)
	       .moveTo(128, 0)
	       .setTweenWeight(4)
	       .onTweenComplete([]{
		       state = State::Init;
		   });
       }

       void enemyDamage( LiveActor *actor ){
	   if( actor->hp ) return;
	   ((Enemy *) actor)->destroy();
       }

       void enemyShoot( Enemy *enemy ){
	   Shot *shot = allocShot( scope.shots, MAX_SHOT_COUNT );
	   if( !shot ) return;
	   shot->init( *enemy, &scope.player, 1, sizeof(scope.player) );
	   shot->frame = 1;

	   shot->dx = random( 1, (int8_t) 3 );
	   if( enemy->x > scope.player.x )
	       shot->dx = -shot->dx;
	   
	   shot->dy = random( 1, (int8_t) 3 );
	   if( enemy->y > scope.player.y )
	       shot->dy = -shot->dy;

       }

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
	   enemy.setAnimation( &enFly ).setTweenWeight(0);
	   enemy.hp = 100;
	   enemy.shoot = enemyShoot;
	   enemy.onDamage = enemyDamage;
	   
	   return true;
       }
	   
    )
