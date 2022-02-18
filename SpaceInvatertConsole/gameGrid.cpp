#include "gameGrid.h"

GameGrid::GameGrid()
{
	for (int y = 0; y < grandeurGrid; y++) {
		for (int x = 0; x < grandeurGrid; x++) {
			grid[x][y] = nullptr;
		}
	}
}

void GameGrid::render(std::ostream& k)
{
	set_cursor(false);
	for (int y = 0; y < grandeurGrid+2; y++) {
		for (int x = 0; x < grandeurGrid + 2; x++) {
			if (y == 0) {
				if (x < 11) {
					k << abs(x - 1)<< ' ';
				}
				else {
					k << abs(x - 1);
				}
			}
			else if (x == 0) {
				if (y < 11) {
					k << abs(y - 1) << ' ';
				}
				else {
					k << abs(y - 1);
				}
			}
			else if (y == grandeurGrid + 1 || x == grandeurGrid + 1){
				k << '#'<< ' ';
			}
			else if (grid[x-1][y-1] == nullptr) {
				k << ' '<< ' ';
			}
			else {
				k << grid[x-1][y-1]->getSymbol()<< ' ';
			}
		}
		std::cout << '\n';
	}
}

//void GameGrid::testdata()
//{
//	for (int y = 0; y < grandeurGrid; y++) {
//		for (int x = 0; x < grandeurGrid; x++) {
//			grid[x][y] = 'D';
//		}
//	}
//}

void GameGrid::setEmplty(int x, int y, bool del)
{
	if(del){ 
		delete grid[x][y]; 
	}
	
	grid[x][y] = nullptr;

}

Entity* GameGrid::checkGrid(int x, int y)
{
	return grid[x][y];
}

bool GameGrid::addEntity(Entity* inEntity)
{
	if ((inEntity->x() >= 0 && inEntity->x() < grandeurGrid) && (inEntity->y() >= 0 && inEntity->y() < grandeurGrid)) {
		grid[inEntity->x()][inEntity->y()] = inEntity;
		return true;
	}
	else {
		return false;
	}
}

void GameGrid::updateEntity(Entity* inEntity)
{

}

void GameGrid::moveEntity(Entity* inEntity, int deltaX, int deltaY)
{
	grid[inEntity->x()][inEntity->y()] = nullptr;
	inEntity->move(deltaX, deltaY);
	grid[inEntity->x()][inEntity->y()] = inEntity;
}

