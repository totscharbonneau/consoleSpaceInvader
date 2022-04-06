#include "gameLoop.h"



Game::Game()
{
    gameGrid1.addEntity(&player1);
    Bullet* recentBullet = nullptr;
    dirEnemy = true;
    playerAlowedtoShoot = true;
    gameOver = false;
    logicRate = 0.153f;
}

void Game::mainGameLoop(int lvl)
{
    char key;
    int value = 0;
    int b=1;
    int battack = 1;

    for (int i = 0; i < lvl; i++) {
        Sleep(500);
        createEnemyLine<Enemy>();
        addEnemies();
    }

    addShield(4, 33, 3, 2);
    addShield(13, 33, 3, 2);
    addShield(24, 33, 3, 2);
    addShield(33, 33, 3, 2);

    Timer* timerupdatelogic = Timer::Instance();

    while (value != KEY_X) {
        
        timerupdatelogic->Tick();

         if (timerupdatelogic->DeltaTime() >= logicRate) {
            timerupdatelogic->reset();
            updateAllBullets();

            if (b % 15 == 0) {
                moveEnemy();
                b = 1;
            }
            if (battack % 5 == 0) {
                enemyAttack(75);
                battack = 1;
            }
            b++;
            battack++;
        }

        if (allDead()) {
            break;
        }
        if (gameOver) {
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
                if (playerAlowedtoShoot) {
                    recentBullet = player1.shoot();
                    liveBullets.push_back(recentBullet);
                    gameGrid1.addEntity(liveBullets.back());
                    playerAlowedtoShoot = false;
                }  
                break;
            case KEY_Y:
               
                break;
            case KEY_PLUS:
                
                changeLogicRate(true);
                
                break;
            case KEY_MOINS:
                changeLogicRate(false);
                break;
            }
        }
        updaterender();
    }
    ClearScreen();
    //trender.stop();
    //tupdate.stop();
    if (gameOver) {
        std::cout << "Game Over" << std::endl;
    }
    else {
        std::cout << "Victoire" << std::endl;
    }
    std::cout << "Score : " << player1.Score() << std::endl;
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
    if (inBullet.y() == 0|| inBullet.y() == grandeurGrid -1) { // bullet touche au haut ou le bas
        removeBullet(NULL, &inBullet);
            return true;
    }
    Entity* nextSpotptr = gameGrid1.checkGrid(inBullet.x(), inBullet.y() + (1 - (2 * inBullet.getWay())));
    int nextSpot;
    if (nextSpotptr == nullptr) {
        nextSpot = TYPE_VOID;
    }
    else if (nextSpotptr->getType() == "enemy") {
        nextSpot = TYPE_ENEMY;
    }
    else if (nextSpotptr->getType() == "bullet") { //rajouter des conditions si nouveau type de projectile
        nextSpot = TYPE_PROJECTILE;
    }
    else if (nextSpotptr->getType() == "player") {
        nextSpot = TYPE_PLAYER;
    }
    else if (nextSpotptr->getType() == "shield") {
        nextSpot = TYPE_SHIELD;
    }

    switch (nextSpot) {
    case TYPE_VOID:
        gameGrid1.moveEntity(&inBullet, 0, (1 - (2 * inBullet.getWay())));
        return true;
    case TYPE_ENEMY:
        removeEnemyinVector((Enemy*)nextSpotptr);
        gameGrid1.setEmplty(inBullet.x(), inBullet.y() + (1 - (2 * inBullet.getWay())), false);
        removeBullet(NULL, &inBullet);
        player1.Score(100);
        return true;
    case TYPE_PROJECTILE:
        removeBullet(NULL,(Bullet*)nextSpotptr);
        removeBullet(NULL, &inBullet);
        return true;
    case TYPE_PLAYER:
        if (!player1.reciveDamage()) {
            gameOver = true;
        }
        removeBullet(NULL, &inBullet);
        return true;
    case TYPE_SHIELD:
        gameGrid1.setEmplty(inBullet.x(), inBullet.y() + (1 - (2 * inBullet.getWay())), false);
        removeBullet(NULL, &inBullet);
        return true;
    }

}

void Game::updateAllBullets()
{
    for (int i = 0; i < liveBullets.size(); i++) {
        if (updateBullet(*liveBullets[i]) == false) {
            removeBullet(i);
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
    if (edge) {
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

bool Game::atEdge()
{
    if (dirEnemy) {
        for (int i = enemyPerLine - 1; i >= 0; i--) {
            for (int j = 0; j < liveEnemy.size(); j++) {
                if (liveEnemy[j][i] != nullptr) {
                    if (liveEnemy[j][i]->x() == grandeurGrid - 1) {
                        return true;
                    }
                    else {
                        return false;
                    }
                }
            }
        }
    }
    else {
        for (int i = 0; i < enemyPerLine; i++) {
            for (int j = 0; j < liveEnemy.size(); j++) {
                if (liveEnemy[j][i] != nullptr) {
                    if (liveEnemy[j][i]->x() == 0) {
                        return true;
                    }
                    else {
                        return false;
                    }
                }
            }
        }
    }
}

void Game::enemyAttack(int ajustValue)
{
    //int v1 = rand() % 100;
    if (rand() % 100 + ajustValue <= 100) return;
    int shootyBoi = rand() % enemyPerLine;
    for (int j = liveEnemy.size() - 1; j >= 0; j--) {
        if (liveEnemy[j][shootyBoi] != nullptr) {
            liveBullets.push_back(liveEnemy[j][shootyBoi]->shoot());
            gameGrid1.addEntity(liveBullets.back());
            return;
        }
    }
}

void Game::removeBullet(int index, Bullet* inbullet)
{
    if (inbullet == recentBullet) {
        playerAlowedtoShoot = true;
    }

    if (inbullet != nullptr) {
        for (int i = 0; i < liveBullets.size(); i++) {
            if (liveBullets[i] == inbullet) {
                index = i;
               
                break;
            }
        }
    }
    gameGrid1.setEmplty(liveBullets[index]->x(), liveBullets[index]->y());
    liveBullets.erase(liveBullets.begin() + index);
}

bool Game::changeLogicRate(bool sens)
{
    if (sens) {
        logicRate -= 0.01f;
    }
    else {
        logicRate += 0.01f;
    }
    return true;
}

void Game::addShield(int inX, int inY, int length, int hight)
{
    if ((inX >= 0 && inX + length < grandeurGrid) && (inY >= 0 && inY+hight < grandeurGrid)) {
        for (int x = inX; x < inX + length; x++) {
            for (int y = inY; y < inY + hight; y++) {
                gameGrid1.addEntity(new Shield(x,y));
            }
       }
    }
}



