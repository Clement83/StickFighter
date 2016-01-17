#include "part.h"

void partUpdate(){
	for(char i = 0; i < _PART_MAX; i ++)
	{
		if (particles[i].lifetime > 0) {
			particles[i].x += particles[i].vx;
			particles[i].y += particles[i].vy;
			
			particles[i].vy += _GRAV_Y;
			particles[i].vx += _GRAV_X;
			
			
			particles[i].lifetime --;
			
			//destroy the particle if it's too much off the screen
			if (particles[i].x < -60 || particles[i].x > 900 || particles[i].y < -50 || particles[i].y > 950)
				particles[i].lifetime = 0;
		}
	}
}

void partCreate(char x, char y,char ranX, char ranY, char numbers){
	char i=0; // index in particles[]
	char j=0; //numbers of particles spawned
	while(j < numbers && i < _PART_MAX){
		if (particles[i].lifetime == 0){
			j ++;
			
			particles[i].x = x*10;
			particles[i].y = y*10;
			
			
			particles[i].vx = random(-ranX,ranX);
			particles[i].vy = random(-ranY,ranY);
			
			particles[i].lifetime = _LIFETIME;
		}
		i++;
	}
}

void partInit(){
	for(char i = 0; i < _PART_MAX; i ++)
	{
		particles[i].lifetime = 0;
	}
}

void partDraw(Gamebuino &gbu, char xOffset, char yOffset){
	for(char i = 0; i < _PART_MAX; i ++)
		if (particles[i].lifetime != 0)
			gbu.display.drawPixel(particles[i].x/10 + xOffset, particles[i].y/10 + yOffset);
}
