uint8_t advModeGroundGen( uint8_t x, uint8_t y){
    uint8_t tileId = noise3( x, y, 50, 80 );
    uint8_t n=0;
    
    if( tileId > 0 ){
	if( noise3(x-1,y,50,80) < tileId ) n |= 1;
	if( noise3(x+1,y,50,80) < tileId ) n |= 2;
	if( noise3(x,y-1,50,80) < tileId ) n |= 4;
	if( noise3(x,y+1,50,80) < tileId ) n |= 8;
    }else{
	if( noise3(x-1,y,50,80) != tileId ) n |= 1;
	if( noise3(x+1,y,50,80) != tileId ) n |= 2;
	if( noise3(x,y-1,50,80) != tileId ) n |= 4;
	if( noise3(x,y+1,50,80) != tileId ) n |= 8;
    }

    uint8_t h = (tileId*2+(n>>3))*8+(n&7);

    return h;
}
