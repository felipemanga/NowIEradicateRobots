STATE( Init,
  {
    Actor girl;
  },
  {
	  scope.girl
		  .moveTo( 20, 16 )
		  .setAnimation( &girlWalk )
		  .show()
		  .flags = ANIM_PLAY;
  },
  {
	  for( uint8_t i=0; i<128/4; ++i )
		  Sprites::drawOverwrite( i*4, 0, bg1, 0 );    
    
  }
       
)
