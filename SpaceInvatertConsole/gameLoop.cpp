#include "gameLoop.h"



Game::Game()
{
    gameGrid1.addEntity(&player1);
    Bullet* recentBullet = nullptr;
    dirEnemy = true;
}

void Game::mainGameLoop(int lvl)
{
    char key;
    int value = 0;
    int b=1;

    for (int i = 0; i < lvl; i++) {
        Sleep(500);
        createEnemyLine<Enemy>();
        addEnemies();
    }

    Timer trender([&]()
        {
            updateAllBullets();
            updaterender();
            if (b++ % 5 == 0) {
                moveEnemy();
                b = 1;
            }
            
        });

    trender.setSingleShot(false);
    trender.setInterval(Timer::Interval(30));
    trender.start(true);



    while (value != KEY_X) {

        if (allDead()) {
            break;
        }

        if (_kbhit()) {
            key = _getch();
            value = key;
            switch (value) {

            case KEY_UP:
                gameGrid1.moveEntity(&player1, 0, -1);
                //std::cout << "up" << std::endl;
                break;
            case KEY_DOWN:
                gameGrid1.moveEntity(&player1, 0, 1);
                //std::cout << "down" << std::endl;
                break;
            case KEY_LEFT:
                gameGrid1.moveEntity(&player1, -1, 0);
                break;
            case KEY_RIGHT:
                gameGrid1.moveEntity(&player1, 1, 0);
                break;
            case KEY_SPACE:
                recentBullet = player1.shoot();
                gameGrid1.addEntity(recentBullet);
                liveBullets.push_back(recentBullet);
                //std::cout << "space" << std::endl;
                break;
            case KEY_Y:
                //liveEnemy[0][0]->shoot();
                /*liveBullets.push_back(liveEnemy[0][0]->shoot());
                gameGrid1.addEntity(liveBullets.back());*/
                //enemyAttack();
                //moveEnemy();

               
                break;
            }
        }
    }
    trender.stop();
}

void Game::ClearScreen()
{
    COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void Game::updaterender()
{
    ClearScreen();
    gameGrid1.render(std::cout);
}

void Game::testGameLoop()
{
    char key;
    int value = 0;
    createEnemyLine<Enemy>();
    addEnemies();
    updaterender();
    Entity* ptrentity = gameGrid1.checkGrid(1, 1);
    std::cout << ptrentity << std::endl;
    Enemy* ptrenemy = (Enemy*)gameGrid1.checkGrid(1, 1);
    std::cout << ptrenemy << std::endl;
    Enemy* penemhy = liveEnemy[0][0];
    bool test = penemhy == ptrenemy;
    //liveEnemy.erase(std::remove(liveEnemy.begin(), liveEnemy.end(), penemhy), liveEnemy.end());
    removeEnemyinVector(ptrenemy);
    //gameGrid1.checkGrid();
}

bool Game::updateBullet(Bullet& inBullet)
{   
    if (inBullet.getWay()) {
        
        if (inBullet.y() == 0) { // bullet touche au haut
            return false;
        }
        else if (gameGrid1.checkGrid(inBullet.x(), inBullet.y()-1) == nullptr) {
            gameGrid1.moveEntity(&inBullet, 0, -1);
            return true;
        }
        else if(gameGrid1.checkGrid(inBullet.x(), inBullet.y() - 1)->getType() == "enemy") {
            //(Enemy*) gameGrid1.checkGrid(inBullet.x(), inBullet.y() - 1);
            removeEnemyinVector((Enemy*)(gameGrid1.checkGrid(inBullet.x(), inBullet.y() - 1)));
            gameGrid1.setEmplty(inBullet.x(), inBullet.y() - 1,false);
            return false;
        }
    }
    else
    {
        if (inBullet.y() == grandeurGrid - 1) { // bullet touche au bas
            return false;
        }
        else if (gameGrid1.checkGrid(inBullet.x(), inBullet.y() + 1) == nullptr) {
            gameGrid1.moveEntity(&inBullet, 0, +1);
            return true;
        }
    }
}

void Game::updateAllBullets()
{
    for (int i = 0; i < liveBullets.size(); i++) {
        if (updateBullet(*liveBullets[i]) == false) {
            gameGrid1.setEmplty(liveBullets[i]->x(), liveBullets[i]->y());
            liveBullets.erase(liveBullets.begin() + i);
        }
    }
}

void Game::addEnemies()
{
    for (int j = 0; j < liveEnemy.size(); j++) {
        for (int i = 0; i < enemyPerLine; i++) {
            gameGrid1.addEntity(liveEnemy[j][i]);
        }
    }
}

void Game::removeEnemyinVector(Enemy* inEnemy)
{
    for (int j = 0; j < liveEnemy.size(); j++) {
        for (int i = 0; i < enemyPerLine; i++) {
            if (liveEnemy[j].at(i) == inEnemy) {
                //liveEnemy[j].erase(std::remove(liveEnemy[j].begin(), liveEnemy[j].end(), inEnemy), liveEnemy[j].end());
                delete liveEnemy[j][i];
                liveEnemy[j][i] = nullptr;
                

                return;
            }
        }
    }
}

bool Game::allDead()
{
    for (int j = 0; j < liveEnemy.size(); j++) {
        for (int i = 0; i < enemyPerLine; i++) {
            if (liveEnemy[j][i] != nullptr) {
                return false;

            }
        }
    }
    return true;
}

void Game::moveEnemy()
{
    int edge = atEdge();
    if (edge == 0) {
        for (int j = 0; j < liveEnemy.size(); j++) {
            for (int i = 0; i < enemyPerLine; i++) {
                if (liveEnemy[j][i] != nullptr) {
                    gameGrid1.moveEntity(liveEnemy[j][i], 0, +1*speed);
                }
            }
        }
        dirEnemy = !dirEnemy;
        return;
    }
    for (int j = 0; j < liveEnemy.size(); j++) {
        for (int i = 0; i < enemyPerLine; i++) {
            if (liveEnemy[j][i] != nullptr) {
                gameGrid1.moveEntity(liveEnemy[j][i], (-1 + (dirEnemy * 2)), 0);
            }
        }
    }
}

int Game::atEdge()
{
    for (int j = 0; j < liveEnemy.size(); j++) {
        for (int i = 0; i < enemyPerLine; i++) {
            if (liveEnemy[j][i] != nullptr) {
                if (dirEnemy) {
                    if ( 3 >= grandeurGrid - 1 - 3 * (enemyPerLine - 1 - i) - liveEnemy[j][i]->x()) {
                        return (grandeurGrid - 1 - 3 * (enemyPerLine - 1 - i) - liveEnemy[j][i]->x());
                    }
                    else {
                        return -1;
                    }
                }
                else {
                    if (liveEnemy[j][i]->x() == 2 * i) {
                        return 0;
                    }
                    else {
                        return -1;
                    }
                }

            }
        }
    }
}

void Game::enemyAttack()
{
    //int v1 = rand() % 100;
    if (rand() % 100 + 50 != 100) return;
    int shootyBoi = rand() % enemyPerLine;
    for (int j = liveEnemy.size() - 1; j >= 0; j--) {
        if (liveEnemy[j][shootyBoi] != nullptr) {
            liveBullets.push_back(liveEnemy[j][shootyBoi]->shoot());
            gameGrid1.addEntity(liveBullets.back());
            return;
        }
    }
}


