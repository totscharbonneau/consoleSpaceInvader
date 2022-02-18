#include "enemy.h"

Enemy::Enemy(int inX, int inY)
{
	symbol = 'V';
	setCoords(inX, inY);
	type = "enemy";
}

Bullet* Enemy::shoot()
{
	Bullet* enemybullet = new Bullet(x(), y(), false);
	return enemybullet;
}