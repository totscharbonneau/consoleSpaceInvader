#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"
#include "bullet.h"

class Player : public Entity
{
public:
	Player();
	Bullet* shoot();
	bool reciveDamage();
	int Score();
	void Score(int inPoints);
	int hitPoints;
private:
	int scorePoints;
};
#endif // !PLAYER_H
