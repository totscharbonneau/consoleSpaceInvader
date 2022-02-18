#pragma once
#ifndef BULLET_H
#define BULLET_H
#include "entity.h"

class Bullet : public Entity
{
public:
	Bullet(int inX, int inY, bool direction);
	bool getWay();
private:
	bool upOdown; // 1 = up, 0 = down
};
#endif // !BULLET_H
