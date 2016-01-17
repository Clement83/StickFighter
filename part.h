#ifndef PART_H
#define PART_H

/**
#Particule by valden
**/

#define _PART_MAX 10
#define _GRAV_X 0
#define _GRAV_Y 6
#define _LIFETIME 20

void partUpdate();

void partCreate(char x, char y,char ranX, char ranY, char numbers);

void partDraw(Gamebuino &gbu, char xOffset, char yOffset);

void partInit();


struct _part{
	int x;
	int y;
	char vx;
	char vy;
	unsigned char lifetime; //0 = dead
};

_part particles[_PART_MAX];

#endif // PART_H
