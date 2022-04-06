#include "entity.h"

Entity::Entity(int inX, int inY, char inSymbol)
{
	symbol = inSymbol;
	coords.x = inX;
	coords.y = inY;
}

const int Entity::x()
{
	return coords.x;
}

const int Entity::y()
{
	return coords.y;
}

void Entity::setCoords(int x, int y)
{
	coords.x = x;
	coords.y = y;
}

char Entity::getSymbol()
{
	return symbol;
}

void Entity::move(int deltaX, int deltaY)
{
	if ((coords.x + deltaX) < 0) {
		coords.x = 0;
	}
	else if ((coords.x + deltaX) >= grandeurGrid) {
		coords.x = grandeurGrid -1;
	}
	else if ((coords.y + deltaY) < 0) {
		coords.y = 0;
	}
	else if ((coords.y + deltaY) >= grandeurGrid) {
		coords.y = grandeurGrid - 1;
	}
	else {
		coords.x += deltaX;
		coords.y += deltaY;
	}
}

const std::string Entity::getType()
{
	return type;
}

