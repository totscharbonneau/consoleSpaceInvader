#include "player.h"

Player::Player()
{
	symbol = 'U';
	setCoords(19, 38);
	type = "player";
	hitPoints = 3;
}

Bullet* Player::shoot()
{
	Bullet *currentBullet = new Bullet(x(), y(), true);
	return currentBullet;
}

bool Player::reciveDamage()
{
	if (--hitPoints == 0) {
		return false;
	}
	return true;
};
