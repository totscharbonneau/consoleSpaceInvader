#include "bullet.h"

Bullet::Bullet(int inX, int inY, bool direction)
{
	symbol = 'B';
	setCoords(inX, inY + (1-(direction*2)));
	upOdown = direction;
	type = "bullet";
}

bool Bullet::getWay()
{
	return upOdown;
}
