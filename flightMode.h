struct FlightModePlayer : public LiveActor {
			   
    bool inputEnabled;
    int8_t accX;
    int8_t accY;
    int16_t speedX;
    int16_t speedY;
	       
    Actor &init();

    void update(){
	LiveActor::update();
	if( !inputEnabled )
	    return;
	
	if( isPressed(LEFT_BUTTON) )
	    accX = -1;
	else if( isPressed(RIGHT_BUTTON) )
	    accX = 1;
	else if( speedX > 0 )
	    accX = -1;
	else if( speedX < 0 )
	    accX = 1;
	else
	    accX = 0;
		   
	speedX += accX * 25;
	if( speedX > 500 )
	    speedX = 500;
	if( speedX < -500 )
	    speedX = -500;
		   
	if( (xH < 0 && speedX < 0) || (speedX > 0 && (x+speedX<x)) )
	    speedX = 0;
		   
	x += speedX;

	if( isPressed(UP_BUTTON) )
	    accY = -1;
	else if( isPressed(DOWN_BUTTON) )
	    accY = 1;
	else if( speedY > 0 )
	    accY = -1;
	else if( speedY < 0 )
	    accY = 1;
	else
	    accY = 0;
		   
	speedY += accY * 30;
	if( speedY > 700 )
	    speedY = 700;
	if( speedY < -700 )
	    speedY = -700;
		   
	if(
	    (yH < 0 && speedY < 0) ||
	    (speedY > 0 && (y+speedY>0x3C00))
	    )
	    speedY = 0;
		   
	y += speedY;

    }
			   
};

Actor &FlightModePlayer::init(){
    Actor::init()
	.setAnimation( &miniFlightUnit )
	.show()
	;
    flags |= ANIM_INVERT;
    inputEnabled = false;
    accX = 0;
    accY = 0;
    speedX = 0;
    speedY = 0;
    immune = 0;
    hp = 100;
    return *this;
}

uint8_t flightModeGroundGen( uint8_t x, uint8_t y){
    uint8_t tileId = noise1( x, y, 80 );
    uint8_t n=0;
    
    if( tileId > 0 ){
	if( noise1(x-1,y,80) < tileId ) n |= 1;
	if( noise1(x+1,y,80) < tileId ) n |= 2;
	if( noise1(x,y-1,80) < tileId ) n |= 4;
	if( noise1(x,y+1,80) < tileId ) n |= 8;
    }else{
	if( noise1(x-1,y,80) != tileId ) n |= 1;
	if( noise1(x+1,y,80) != tileId ) n |= 2;
	if( noise1(x,y-1,80) != tileId ) n |= 4;
	if( noise1(x,y+1,80) != tileId ) n |= 8;
    }

    uint8_t h = (tileId*2+(n>>3))*8+(n&7);

    return h;
}

