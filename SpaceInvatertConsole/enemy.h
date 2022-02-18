#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include "bullet.h"

class Enemy : public Entity
{
public:
	Enemy(int inX = 0, int inY = 0);
	virtual Bullet* shoot(); // virtual pure quand different enemy existes
};
#endif // !ENEMY_H
