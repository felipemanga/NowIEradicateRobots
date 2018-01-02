STATE( Init,
       {
	   Actor girl;
	   uint8_t steps;
	
	   Actor fu;

       },
       {
	   playChiptune([](uint16_t t){
		   return t>>4|t>>5|t;
	       });
	   
	   clearScreen = CLEAR_WHITE;
	   scope.steps = 0;
	  
	   scope.fu
	       .init()
	       .setPosition( 64, 128+16 )
	       .moveTo( 64, 32 )
	       .setTweenWeight( 4 )
	       .setAnimation( &flightUnitFly )
	       .onTweenComplete([]{
		       scope.fu
			   .onTweenComplete([]{
				   state = State::Level1;
			       })
			   .moveTo( 64, -32 )
			   .setTweenWeight( 2 );
		   })
	       .flags = ANIM_PLAY
	       ;
	  	  		  
	   scope.girl
	       .init()
	       .setPosition( -20, 16 )
	       .setAnimation( &girlWalk )
	       .show()
	       .onAnimationComplete([]{
		       scope.steps++;
		       if( scope.steps >= 5 )
			   start();
		   })
	       .flags = ANIM_PLAY | ANIM_GRAY;
	  
       },
       {
	  
	   if( justPressed(A_BUTTON) && scope.steps < 5 ){
	       scope.steps = 5;
	       start();
	   }
    
       },
       void start(){		   
	   scope.fu.show();
	   scope.girl.hide();		   
       }	  
)
