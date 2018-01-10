STATE( AdvMode,
       {
	   TileWindow ground;
	   Actor fu;
	   Actor player;
	   bool inputEnabled;
       },
       {
	   scope.inputEnabled = false;
	   seed = 0xBEEF;
	   seedSequence = 0;
	   scope.ground.init( tiles, advModeGroundGen );

	   playChiptune([](uint16_t t){
		   return (t>>8)&~(t>>5|t>>6|t>>1);
	       });

	   initEnemies();
	   initShots();
	   
	   after.init();
	   
	   scope.player
	       .init()
	       .setPosition(64,32)
	       .setAnimation(&enFly)
	       .show()
	       .actorFlags = ACTOR_HIDDEN;
	   
	   scope.fu
	       .init()
	       .setAnimation( &miniFlightUnit )
	       .show()
	       .setPosition(0, -32)
	       .moveTo(64, 32)
	       .setTweenWeight( 3 )
	       .onTweenComplete([]{
		       scope.inputEnabled = true;
		       cameraShakeY = 20;
		       scope.player.actorFlags = 0;
		       scope.fu
			   .moveTo( 127, -32 )
			   .setTweenWeight( 6 )
			   .onTweenComplete([]{
				   scope.fu.hide();
			       });
		   })
	       .flags |= ANIM_INVERT;

       },
       {
	   move();
	   scope.ground.render();
	   // updateEnemies();
       },

       void move(){
	   if( !scope.inputEnabled )
	       return;
	       
	   if( isPressed(UP_BUTTON) )
	       scope.ground.speedY = 1;
	   else if( isPressed(DOWN_BUTTON) )
	       scope.ground.speedY = -1;
	   else
	       scope.ground.speedY = 0;

	   if( isPressed(RIGHT_BUTTON) )
	       scope.ground.speedX = -1;
	   else if( isPressed(LEFT_BUTTON) )
	       scope.ground.speedX = 1;
	   else
	       scope.ground.speedX = 0;
	       
       }

       void spawnAdvEnemy( int8_t x, int8_t y ){

	   auto enemyp = allocEnemy();
	   if( !enemyp ) return;
	   
	   auto enemy = *enemyp;
	   enemy.data = &scope.player;
	   enemy.ai = tileWalkerAI;
	   enemy.timeAlive = 1;
	   enemy.setAnimation( &enFly );
	   enemy.setPosition( 10, 10 );
	   enemy.flags |= ANIM_INVERT;
	   /*
	   scope.ground.tileToScreen( enemy.x, enemy.y );
	   enemy.x <<= 8;
	   enemy.y <<= 8;
	   */
	   enemy.hp = 30;

       }

       uint8_t advModeGroundGen( uint8_t x, uint8_t y){
	   uint8_t tileId = noise3( x, y, 50, 80 );
	   uint8_t n=0;
    
	   if( tileId > 0 ){
	       if( noise3(x-1,y,50,80) < tileId ) n |= 1;
	       if( noise3(x+1,y,50,80) < tileId ) n |= 2;
	       if( noise3(x,y-1,50,80) < tileId ) n |= 4;
	       if( noise3(x,y+1,50,80) < tileId ) n |= 8;
	       // if( !n && random(0, (int8_t) 100) < 10 )
		   spawnAdvEnemy( x, y );
	   }else{
	       if( noise3(x-1,y,50,80) != tileId ) n |= 1;
	       if( noise3(x+1,y,50,80) != tileId ) n |= 2;
	       if( noise3(x,y-1,50,80) != tileId ) n |= 4;
	       if( noise3(x,y+1,50,80) != tileId ) n |= 8;
	   }

	   uint8_t h = (tileId*2+(n>>3))*8+(n&7);

	   return h;
       }
       
    )
