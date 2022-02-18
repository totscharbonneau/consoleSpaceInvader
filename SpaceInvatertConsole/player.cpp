#include "player.h"

Player::Player()
{
	symbol = 'U';
	setCoords(19, 38);
	type = "player";
}

Bullet* Player::shoot()
{
	Bullet *currentBullet = new Bullet(x(), y(), true);
	return currentBullet;
}
