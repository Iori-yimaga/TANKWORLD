#include "tank.h"
#include "game.h"
#include <time.h>
#include <stdlib.h>

// 枚举方向
enum DIRS {
	up,
	down,
	left,
	right
};

//srand((unsigned)time(NULL));

// 敌军构造
ANAMY::ANAMY(MAP& map):TANK(map) {
	// 坦克核心
	this->getPos()[0].setX(4);
	this->getPos()[0].setY(4);
	// 初始形态向右边
	this->setRIGHT();
	// 初始方向为右
	this->setADir(right);
	// 初始化炮弹
	this->getBullet().setSpeed(50);
	// 初始化运动速度
	this->aspeed = 200;
	// 画出坦克
	this->showTank(map);
}

// 敌军析构
//ANAMY::~ANAMY() {
//	
//}

//设定时钟
void ANAMY::setAClock() {
	this->aclock = clock();
}

// 获取时钟
int ANAMY::getAClock() {
	return this->aclock;
}

// 画坦克
void ANAMY::showTank(MAP& map) {
	for (int i = 0; i < 6; i++) {
		map.setAllSth(getPos()[i].getX(), getPos()[i].getY(), TANKOT);
	}
	PrintChar(getPos()[0].getX(), getPos()[0].getY(), "A");
	for (int i = 1; i < 6; i++) {
		PrintChar(getPos()[i].getX(), getPos()[i].getY(), "■");
	}
}

// 自动移动
void ANAMY::autoMoving(MAP& map) {
	if ((this->getTAlive() == true) && (clock() - this->getAClock() > this->getASpeed())) {
		// 擦除坦克
		this->wipeTank(map);
		// 重置计时器
		this->setAClock();
		switch (this->getADir()) {
			case up: {
				this->setUP();
				// 判定是否为障碍物、河流、家，是则不能穿过
				if (map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() - 1] == OBSTACLE || map.getAllSth()[getPos()[1].getX() - 1][getPos()[1].getY()] == OBSTACLE || map.getAllSth()[getPos()[1].getX() + 1][getPos()[1].getY()] == OBSTACLE ||
					map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() - 1] == RIVER    || map.getAllSth()[getPos()[1].getX() - 1][getPos()[1].getY()] == RIVER    || map.getAllSth()[getPos()[1].getX() + 1][getPos()[1].getY()] == RIVER ||
					map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() - 1] == HOME     || map.getAllSth()[getPos()[1].getX() - 1][getPos()[1].getY()] == HOME     || map.getAllSth()[getPos()[1].getX() + 1][getPos()[1].getY()] == HOME ||
					map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() - 1] == FLAG     || map.getAllSth()[getPos()[1].getX() - 1][getPos()[1].getY()] == FLAG     || map.getAllSth()[getPos()[1].getX() + 1][getPos()[1].getY()] == FLAG ||
					map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() - 1] == GLASS    || map.getAllSth()[getPos()[1].getX() - 1][getPos()[1].getY()] == GLASS    || map.getAllSth()[getPos()[1].getX() + 1][getPos()[1].getY()] == GLASS
					) {
					// 生成新的方向
					this->setADir(rand() % 4);
				}
				else {
					for (int i = 0; i < 6; i++) {
						int ty = getPos()[i].getY();
						getPos()[i].setY(--ty);
					}
				}
				break;
			}
			case down: {
				setDOWN();
				// 判定是否为障碍物、河流、家，是则不能穿过
				if (map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() + 1] == OBSTACLE || map.getAllSth()[getPos()[1].getX() - 1][getPos()[1].getY()] == OBSTACLE || map.getAllSth()[getPos()[1].getX() + 1][getPos()[1].getY()] == OBSTACLE ||
					map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() + 1] == RIVER    || map.getAllSth()[getPos()[1].getX() - 1][getPos()[1].getY()] == RIVER    || map.getAllSth()[getPos()[1].getX() + 1][getPos()[1].getY()] == RIVER ||
					map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() + 1] == HOME     || map.getAllSth()[getPos()[1].getX() - 1][getPos()[1].getY()] == HOME     || map.getAllSth()[getPos()[1].getX() + 1][getPos()[1].getY()] == HOME ||
					map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() + 1] == FLAG     || map.getAllSth()[getPos()[1].getX() - 1][getPos()[1].getY()] == FLAG     || map.getAllSth()[getPos()[1].getX() + 1][getPos()[1].getY()] == FLAG ||
					map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() + 1] == GLASS    || map.getAllSth()[getPos()[1].getX() - 1][getPos()[1].getY()] == GLASS    || map.getAllSth()[getPos()[1].getX() + 1][getPos()[1].getY()] == GLASS
					) {
					// 生成新的方向
					this->setADir(rand() % 4);
				}
				else {
					for (int i = 0; i < 6; i++) {
						int ty = getPos()[i].getY();
						getPos()[i].setY(++ty);
					}
				}
				break;
			}
			case left: {
				setLEFT();
				// 判定是否为障碍物、河流、家，是则不能穿过
				if (map.getAllSth()[getPos()[1].getX() - 1][getPos()[1].getY()] == OBSTACLE || map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() - 1] == OBSTACLE || map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() + 1] == OBSTACLE ||
					map.getAllSth()[getPos()[1].getX() - 1][getPos()[1].getY()] == RIVER    || map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() - 1] == RIVER    || map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() + 1] == RIVER ||
					map.getAllSth()[getPos()[1].getX() - 1][getPos()[1].getY()] == HOME     || map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() - 1] == HOME     || map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() + 1] == HOME ||
					map.getAllSth()[getPos()[1].getX() - 1][getPos()[1].getY()] == FLAG     || map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() - 1] == FLAG     || map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() + 1] == FLAG ||
					map.getAllSth()[getPos()[1].getX() - 1][getPos()[1].getY()] == GLASS    || map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() - 1] == GLASS    || map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() + 1] == GLASS
					) {
					// 生成新的方向
					this->setADir(rand() % 4);
				}
				else {
					for (int i = 0; i < 6; i++) {
						int tx = getPos()[i].getX();
						getPos()[i].setX(--tx);
					}
				}
				break;
			}
			case right: {
				setRIGHT();
				// 判定是否为障碍物、河流、家，是则不能穿过
				if (map.getAllSth()[getPos()[1].getX() + 1][getPos()[1].getY()] == OBSTACLE || map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() - 1] == OBSTACLE || map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() + 1] == OBSTACLE ||
					map.getAllSth()[getPos()[1].getX() + 1][getPos()[1].getY()] == RIVER    || map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() - 1] == RIVER    || map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() + 1] == RIVER ||
					map.getAllSth()[getPos()[1].getX() + 1][getPos()[1].getY()] == HOME     || map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() - 1] == HOME     || map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() + 1] == HOME ||
					map.getAllSth()[getPos()[1].getX() + 1][getPos()[1].getY()] == FLAG     || map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() - 1] == FLAG     || map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() + 1] == FLAG ||
					map.getAllSth()[getPos()[1].getX() + 1][getPos()[1].getY()] == GLASS    || map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() - 1] == GLASS    || map.getAllSth()[getPos()[1].getX()][getPos()[1].getY() + 1] == GLASS
					) {
					// 生成新的方向
					this->setADir(rand() % 4);
				}
				else {
					for (int i = 0; i < 6; i++) {
						int tx = getPos()[i].getX();
						getPos()[i].setX(++tx);
					}
				}
				break;
			}
			default:
				break;
		}
		
		// 只有敌军存活才会打印
		if (getTAlive() == true) {
			this->showTank(map);
		}
	}
}

// 自动射击
void ANAMY::autoShooting(MAP& map) {
	
}

// 获取敌军移动速速
int ANAMY::getASpeed() {
	return this->aspeed;
}

// 设定敌军坦克方向
void ANAMY::setADir(int _dir) {
	this->adir = _dir;
}

// 获取敌军坦克方向
int ANAMY::getADir() {
	return this->adir;
}