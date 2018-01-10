STATE( FightMode,
       {
	   Actor player;
       },
       {
	   clearScreen = CLEAR_GRAY;
	   scope.player.init()
	       .setAnimation( &girlIdle )
	       .show()
	       .flags = ANIM_PLAY; // | ANIM_GRAY;
       },
       {
	   if( scope.player.animation == &girlIdle )
	       if( isPressed(RIGHT_BUTTON) )
		   scope.player
		       .setAnimation( &girlWalk )
		       .onAnimationComplete( idle );
	       else if( isPressed(LEFT_BUTTON) )
		   scope.player
		       .setAnimation( &girlBack )
		       .onAnimationComplete( idle );
       },

       void idle(){
	   scope.player.setAnimation( &girlIdle )
	       .onAnimationComplete(NULL);	   
       }
       
    )
