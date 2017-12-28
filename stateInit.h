STATE( Init,
  {
    uint8_t frame;
    int16_t x, y;    
  },
  {
    Init.x = -20;
    Init.y =  16;
    Init.frame = 0;
  },
  {
    
    for( uint8_t i=0; i<128/4; ++i ){
      Sprites::drawOverwrite( i*4, 0, bg1, 0 );
    }
    Init.x += (int8_t) pgm_read_byte( offset+Init.frame*2 );
    Init.y += (int8_t) pgm_read_byte( offset+Init.frame*2+1 );
    if( Init.x > 128 ) Init.x = -20;
  
    arduboy.drawCompressed(
			   Init.x,
			   Init.y,
			   pgm_read_word(walk+Init.frame*2)
			   );

    arduboy.drawCompressed(
			   Init.x,
			   Init.y,
			   pgm_read_word(walk+Init.frame*2+1),
			   0
			   );

    Init.frame = (Init.frame+1) % 8;
    
  }
       
)
