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
	       .flags = ANIM_PLAY; // | ANIM_GRAY;
	   idle();
       },
       {
	   if( scope.isIdle )
	       if( isPressed(RIGHT_BUTTON) )
		   setAnimation( &girlWalk );
	       else if( isPressed(LEFT_BUTTON) )
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
