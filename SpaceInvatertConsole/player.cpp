#include "player.h"

Player::Player()
{
	symbol = 'U';
	setCoords(19, 38);
	type = "player";
	hitPoints = 3;
	scorePoints = 0;
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

// fonction pour retourner le nombre de points

int Player::Score() {
	return scorePoints;
}

// fonction pour modifier le nombre de points

void Player::Score(int inPoints) {
	scorePoints += inPoints;
}