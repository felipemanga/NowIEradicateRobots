STATE( FightMode,
       {
	   Actor player;
	   bool isIdle;
       },
       {
	   playChiptune([](uint16_t t){
		   return ~(t>>5|t>>6|t)-1;
	       });
	   clearScreen = CLEAR_GRAY;
	   scope.player.init()
	       .show()
	       .actorFlags = ACTOR_PLAY;
	   idle();
       },
       {
	   if( !scope.isIdle )
	       return;
	   
	   bool mirrored = scope.player.xH > 64;
	   int8_t walk = !!isPressed(RIGHT_BUTTON) - !!isPressed(LEFT_BUTTON);
	   
	   if( mirrored ){
	       scope.player.actorFlags |= ACTOR_MIRROR;
	       walk = -walk;
	   }else
	       scope.player.actorFlags &= ~ACTOR_MIRROR;	  
	   
	   if( walk>0 )
	       setAnimation( &girlWalk );
	   else if( walk<0 )
	       setAnimation( &girlBack );
	   else if( isPressed(DOWN_BUTTON) )
	       scope.player
		   .setAnimation( &girlDuck )
		   .onAnimationComplete( idle );
	   else if( isPressed(A_BUTTON) )
	       changeState( State::FlightMode, 0xFF );
	   else if( isPressed(B_BUTTON) )
	       changeState( State::AdvMode, 0x00 );
       },

       void idle(){
	   scope.player.setAnimation( &girlIdle )
	       .onAnimationComplete(NULL);
	   scope.isIdle = true;
       }

       void setAnimation( const void *anim ){
	   scope.player.setAnimation( anim )
	       .onAnimationComplete( idle );
	   scope.isIdle = false;
       }
       
    )
