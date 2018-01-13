STATE( Init,
       {
	   Actor girl;
	   uint8_t steps;
	   Actor title;
	   Actor fu;

       },
       {
	   playChiptune([](uint16_t t){
		   return t>>5|t>>6|t>>1;
	       });
	   
	   clearScreen = CLEAR_WHITE;
	   scope.steps = 0;

	   scope.title
	       .init()
	       .setPosition( 0, 64 )
	       .setAnimation( &titleAnim )
	       .flags |= ANIM_INVERT;
	  
	   scope.fu
	       .init()
	       .setPosition( 64, 128+16 )
	       .moveTo( 64, 32 )
	       .setTweenWeight( 4 )
	       .setAnimation( &flightUnitFly )
	       .onTweenComplete([]{
		       scope.fu
			   .onTweenComplete([]{
				   state = State::AdvMode;
//				   changeState( State::FightMode, 0xAA );
			       })
			   .moveTo( 64, -32 )
			   .setTweenWeight( 2 );
		   })
	       .actorFlags = ACTOR_PLAY
	       ;
	  	  		  
	   scope.girl
	       .init()
	       .setPosition( -20, 16 )
	       .setAnimation( &girlWalk )
	       .show()
	       .onAnimationComplete([]{
		       scope.steps++;
		       if( scope.steps >= 5 ){			   
			   scope.steps = 6;
			   scope.title
			       .moveTo(0, 0)
			       .setTweenWeight(2)
			       .show();
			   scope.girl.hide();
		       }
		   })
	       .setFlags( ANIM_GRAY, ACTOR_PLAY );
	  
       },
       {

	   if( justPressed(UP_BUTTON) )
	       scope.girl.actorFlags ^= ACTOR_MIRROR;
	  
	   if( justPressed(A_BUTTON) && scope.steps < 7 ){
	       scope.steps = 7;
	       scope.fu.show();
	       scope.title.hide();
	       scope.girl.hide();
	   }

	   if( justPressed(B_BUTTON) ){
	       Arduboy2Audio::toggle();
	       Arduboy2Audio::saveOnOff();
	   }	   
    
       }
       
    )
