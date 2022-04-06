#pragma once
#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "gameGrid.h"
#include "player.h"
#include <conio.h>
#include <windows.h>
#include "timer2.h"
#include "bullet.h"
#include <vector>
#include "enemy.h"
#include <algorithm>
#include "shield.h"
#include <iostream>
#include <string>
#include "include/json.hpp"
#include "include/serial/SerialPort.hpp"

#define BAUD 460800           // Frequence de transmission serielle
#define MSG_MAX_SIZE 1024     // Longueur maximale d'un message
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_X 120
#define KEY_Y 121
#define KEY_SPACE 32
#define KEY_PLUS 61
#define KEY_MOINS 45
#define TYPE_ENEMY 151
#define TYPE_VOID 150
#define TYPE_PROJECTILE 152
#define TYPE_PLAYER 153
#define TYPE_SHIELD 154
#define THRESHOLD 255

using namespace std;
using json = nlohmann::json;


struct joystick_Axes
{
	int X = 0;
	int Y = 0;
};
struct ADXL
{
	int X = 0;
	int Y = 0;
	int Z = 0;
};

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
	bool changeLogicRate(bool sens);
	void addShield(int inX, int inY, int length, int hight);
	bool SendToSerial(SerialPort* arduino, json j_msg);
	bool RcvFromSerial(SerialPort* arduino, string& msg);
	void getButtonValues(int btnRegister);

	std::vector<Bullet*> liveBullets;
	joystick_Axes m_joystick;
	ADXL m_accel;
	int m_Btn_States[5] = { 0,0,0,0,0 };
	float m_Game_Speed = 1.0f;
	void initCom();
	void requestInputs();
	json j_msg_send, j_msg_rcv; // Structure de donnees JSON pour envoie et reception
	string raw_msg, com;

private:
	std::vector< std::vector<Enemy*>> liveEnemy;
	GameGrid gameGrid1;
	Player player1;
	Bullet* recentBullet;
	bool dirEnemy; // 1 = droite/ 2 = gauche
	bool playerAlowedtoShoot;
	bool gameOver;
	float logicRate;
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
