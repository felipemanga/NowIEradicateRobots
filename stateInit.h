STATE( Init,
  {
    Actor girl;
  },
  {
    scope.girl.xH = 20;
    scope.girl.yH = 16;
    scope.girl.frame = 0;
    scope.girl.animation = &girlWalk;
    scope.girl.flags = ANIM_PLAY;
  },
  {
    
    for( uint8_t i=0; i<128/4; ++i ){
      Sprites::drawOverwrite( i*4, 0, bg1, 0 );
    }
    
    draw( scope.girl );
    
  }
       
)
