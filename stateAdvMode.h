STATE( AdvMode,
       {
	   TileWindow ground;
       },
       {
	   seed = 0xBEEF;
	   seedSequence = 0;
	   scope.ground.init( tiles, advModeGroundGen );
       },
       {
	   
	   if( isPressed(UP_BUTTON) )
	       scope.ground.speedY = 1;
	   else if( isPressed(DOWN_BUTTON) )
	       scope.ground.speedY = -1;
	   else
	       scope.ground.speedY = 0;

	   if( isPressed(RIGHT_BUTTON) )
	       scope.ground.speedX = 1;
	   else if( isPressed(LEFT_BUTTON) )
	       scope.ground.speedX = -1;
	   else
	       scope.ground.speedX = 0;
	   
	   scope.ground.render();
       }
    )
