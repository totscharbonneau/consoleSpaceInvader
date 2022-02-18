#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "coordonnee.h"
#include "setting.h"
#include <string>

class Entity
{
protected:
	Coordonnee coords;
	char symbol;
	std::string type;
public:
	Entity(int inX = 0, int inY = 0, char inSymbol = '0');
	const int x();
	const int y();
	void setCoords(int x, int y);
	char getSymbol();
	void move(int deltaX, int deltaY);
	const std::string getType();
	
};
#endif // !ENTITY_H
