#pragma once
#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "gameGrid.h"
#include "player.h"
#include <conio.h>
#include <windows.h>
#include "timer.h"
#include "bullet.h"
#include <vector>
#include "enemy.h"
#include <algorithm>


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_X 120
#define KEY_Y 121
#define KEY_SPACE 32
#define TYPE_ENEMY 151
#define TYPE_VOID 150
#define TYPE_PROJECTILE 152
#define TYPE_PLAYER 153

class Game {
public:
	Game();
	void mainGameLoop(int lvl);
	void ClearScreen();
	void updaterender();
	void testGameLoop();
	bool updateBullet(Bullet & inBullet);
	void updateAllBullets();
	template<typename T>
	void createEnemyLine();
	void addEnemies();
	void removeEnemyinVector(Enemy* inEnemy);
	bool allDead();
	void moveEnemy();
	bool atEdge();
	void enemyAttack(int ajustValue);
	void removeBullet(int index, Bullet* inbullet = nullptr);


private:
	std::vector<Bullet*> liveBullets;
	std::vector< std::vector<Enemy*>> liveEnemy;
	GameGrid gameGrid1;
	Player player1;
	Bullet* recentBullet;
	bool dirEnemy; // 1 = droite/ 2 = gauche
	bool playerAlowedtoShoot;
	bool gameOver;
};
#endif // !GAMELOOP_H

template<typename T>
inline void Game::createEnemyLine()
{	
	std::vector<T*> vecteurLine;

    for (int i = 0; i < enemyPerLine; i++) {
        vecteurLine.push_back(new T(vecteurLine.size()*3+1,liveEnemy.size()*3+1));
    }
    liveEnemy.push_back(vecteurLine);
}
