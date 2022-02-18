#pragma once
#ifndef GAMEGRID_H
#define GAMEGRID_H
#include <iostream>
#include "entity.h"
//#include "setting.h"


class GameGrid
{
private:
	Entity* grid[grandeurGrid][grandeurGrid];
public:
	GameGrid();
	void render(std::ostream & k);
	//void testdata();
	void setEmplty(int x, int y, bool del = true);
	Entity* checkGrid(int x, int y);
	bool addEntity(Entity* inEntity);
	void updateEntity(Entity* inEntity);
	void moveEntity(Entity* inEntity, int deltaX, int deltaY);
};
#endif // !GAMEGRID_H
