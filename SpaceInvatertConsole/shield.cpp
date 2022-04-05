#include "shield.h"

Shield::Shield(int inX, int inY) {
	symbol = 'O';
	setCoords(inX, inY);
	type = "shield";
}