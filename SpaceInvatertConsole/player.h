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
private:
	int hitPoints;
};
#endif // !PLAYER_H
