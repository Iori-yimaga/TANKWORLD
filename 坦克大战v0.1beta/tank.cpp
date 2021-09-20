#include "tank.h"
#include "game.h"
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <iostream>

// 子弹类构造
BULLET::BULLET(MAP& map) {
	this->setX(0);
	this->setY(0);
	this->setSpeed(50);
	this->setBAlive(false);
}

// 设置速度
void BULLET::setSpeed(int _speed) {
	this->speed = _speed;
}

// 获取速度
int BULLET::getSpeed() {
	return this->speed;
}

// 设置时钟
void BULLET::setCClock() {
	this->cclock = clock();
}

// 获取时钟
int BULLET::getCClock() {
	return this->cclock;
}

// 设置子弹方向
void BULLET::setBDir(char _tdir) {
	this->bdir = _tdir;
}

// 获取子弹方向
char BULLET::getBDir() {
	return this->bdir;
}

// 设置子弹存在
void BULLET::setBAlive(bool alive) {
	this->balive = alive;
}

// 获取子弹情况
bool BULLET::getBAlive() {
	return this->balive;
}

// 记录上一个地形
void BULLET::setLastLand(int _land) {
	this->lastland = _land;
}

// 获取上一个地形
int BULLET::getLastLand() {
	return this->lastland;
}

// 初始化坦克
TANK::TANK(MAP& map):bullet(map) {
	// 坦克核心
	pos[0].setX(30);
	pos[0].setY(24);
	// 初始化存活
	this->talive = true;
	// 初始置为向上
	this->setUP();
	// 初始化炮弹
	bullet.setSpeed(50);
	// 初始化隐身状态
	this->setStealth(false);
	// 画出坦克
	this->showTank(map);
}

// 析构函数
//TANK::~TANK() {
//	delete[] pos;
//}

// 获取坦克身体节点
NODE* TANK::getPos() {
	return this->pos;
}

// 设置方向
void TANK::setDir(char _tdir) {
	this->direction = _tdir;
}

// 获取方向
char TANK::getDir() {
	return this->direction;
}

// 设置向上方向
void TANK::setUP() {
	this->setDir(UP);
	pos[1].setX(pos[0].getX());
	pos[1].setY(pos[0].getY() - 1);
	pos[2].setX(pos[0].getX() - 1);
	pos[2].setY(pos[0].getY());
	pos[3].setX(pos[0].getX() + 1);
	pos[3].setY(pos[0].getY());
	pos[4].setX(pos[0].getX() - 1);
	pos[4].setY(pos[0].getY() + 1);
	pos[5].setX(pos[0].getX() + 1);
	pos[5].setY(pos[0].getY() + 1);
}
// 设置向下方向
void TANK::setDOWN() {
	this->setDir(DOWN);
	pos[1].setX(pos[0].getX());
	pos[1].setY(pos[0].getY() + 1);
	pos[2].setX(pos[0].getX() + 1);;
	pos[2].setY(pos[0].getY());
	pos[3].setX(pos[0].getX() - 1);
	pos[3].setY(pos[0].getY());
	pos[4].setX(pos[0].getX() + 1);
	pos[4].setY(pos[0].getY() - 1);
	pos[5].setX(pos[0].getX() - 1);
	pos[5].setY(pos[0].getY() - 1);
}
// 设置向左方向
void TANK::setLEFT() {
	this->setDir(LEFT);
	pos[1].setX(pos[0].getX() - 1);
	pos[1].setY(pos[0].getY());
	pos[2].setX(pos[0].getX());
	pos[2].setY(pos[0].getY() + 1);
	pos[3].setX(pos[0].getX());
	pos[3].setY(pos[0].getY() - 1);
	pos[4].setX(pos[0].getX() + 1);
	pos[4].setY(pos[0].getY() + 1);
	pos[5].setX(pos[0].getX() + 1);
	pos[5].setY(pos[0].getY() - 1);
}
// 设置向右方向
void TANK::setRIGHT() {
	this->setDir(RIGHT);
	pos[1].setX(pos[0].getX() + 1);
	pos[1].setY(pos[0].getY());
	pos[2].setX(pos[0].getX());
	pos[2].setY(pos[0].getY() - 1);
	pos[3].setX(pos[0].getX());
	pos[3].setY(pos[0].getY() + 1);
	pos[4].setX(pos[0].getX() - 1);
	pos[4].setY(pos[0].getY() - 1);
	pos[5].setX(pos[0].getX() - 1);
	pos[5].setY(pos[0].getY() + 1);
}

// 擦除坦克
void TANK::wipeTank(MAP& map) {
	for (int i = 0; i < 6; i++) {
		PrintChar(pos[i].getX(), pos[i].getY(), "  ");
		map.setAllSth(pos[i].getX(), pos[i].getY(), SPACE);
	}
}

// 遍历打印坦克
void TANK::showTank(MAP& map) {
	for (int i = 0; i < 6; i++) {
		PrintChar(pos[i].getX(), pos[i].getY(), "■");
		map.setAllSth(pos[i].getX(), pos[i].getY(), TANKME);
	}
}

// 打印子弹
void TANK::showBullet(MAP& map) {
	PrintChar(bullet.getX(), bullet.getY(), "*");
	map.setAllSth(bullet.getX(), bullet.getY(), BULLETT);
}

// 擦除子弹
void TANK::wipeBullet(MAP& map) {
	PrintChar(bullet.getX(), bullet.getY(), " ");
	map.setAllSth(bullet.getX(), bullet.getY(), SPACE);
}

// 开炮 (移动子弹)
void TANK::attack(MAP& map, ANAMY& anamy) {
	
	// 子弹速度和时钟的关系
	if ((bullet.getBAlive() == true) && (clock() - bullet.getCClock() > bullet.getSpeed())) {
		// 擦除子弹
		if (bullet.getBAlive() == true) {
			this->wipeBullet(map);
		}
		// 重置计时器
		bullet.setCClock();
		// 取出子弹坐标
		int ty = bullet.getY();
		int tx = bullet.getX();
		// 判断子弹方向
		switch (bullet.getBDir()) {
		case UP: {
			bullet.setY(--ty);
			// 还原上一个河流节点
			if (bullet.getLastLand() == RIVER) {
				map.setAllSth(tx, ty + 1, RIVER);
				PrintChar(tx, ty + 1, "≈", BLUE);
			}
			// 还原上一个草丛节点
			if (bullet.getLastLand() == GLASS) {
				map.setAllSth(tx, ty + 1, GLASS);
				PrintChar(tx, ty + 1, "@", GREEN);
			}
			break;
		}
		case DOWN: {
			bullet.setY(++ty);
			// 还原上一个河流节点
			if (bullet.getLastLand() == RIVER) {
				map.setAllSth(tx, ty - 1, RIVER);
				PrintChar(tx, ty - 1, "≈", BLUE);
			}
			// 还原上一个草丛节点
			if (bullet.getLastLand() == GLASS) {
				map.setAllSth(tx, ty - 1, GLASS);
				PrintChar(tx, ty - 1, "@", GREEN);
			}
			break;
		}
		case LEFT: {
			bullet.setX(--tx);
			// 还原上一个河流节点
			if (bullet.getLastLand() == RIVER) {
				map.setAllSth(tx + 1, ty, RIVER);
				PrintChar(tx + 1, ty, "≈", BLUE);
			}
			// 还原上一个草丛节点
			if (bullet.getLastLand() == GLASS) {
				map.setAllSth(tx + 1, ty, GLASS);
				PrintChar(tx + 1, ty, "@", GREEN);
			}
			break;
		}
		case RIGHT: {
			bullet.setX(++tx);
			// 还原上一个河流节点
			if (bullet.getLastLand() == RIVER) {
				map.setAllSth(tx - 1, ty, RIVER);
				PrintChar(tx - 1, ty, "≈", BLUE);
			}
			// 还原上一个草丛节点
			if (bullet.getLastLand() == GLASS) {
				map.setAllSth(tx - 1, ty, GLASS);
				PrintChar(tx - 1, ty, "@", GREEN);
			}
			break;
		}
		default:
			break;
		}
		// 判定子弹碰撞
		if (map.getAllSth()[tx][ty] == SPACE) {
			bullet.setLastLand(SPACE);
		}
		else if (map.getAllSth()[tx][ty] == OBSTACLE) {
			bullet.setBAlive(false);
		}
		else if (map.getAllSth()[tx][ty] == HOME) {
			this->wipeBullet(map);
			bullet.setBAlive(false);
			map.setAllSth(tx, ty, SPACE);
		}
		else if (map.getAllSth()[tx][ty] == RIVER) {
			bullet.setLastLand(RIVER);
		}
		else if (map.getAllSth()[tx][ty] == GLASS) {
			bullet.setLastLand(GLASS);
		}
		else if (map.getAllSth()[tx][ty] == TANKOT) {
			bullet.setBAlive(false);
			anamy.setTAlive(false);
			anamy.wipeTank(map);
		}
		
		// 打印子弹
		if (bullet.getBAlive() == true) {
			this->showBullet(map);
		}
	}
}

// 设置隐身状态
void TANK::setStealth(bool _flag) {
	this->stealthl = _flag;
}

// 获取隐身状态
bool TANK::getStealth() {
	return this->stealthl;
}

// 操作坦克
void TANK::opTank(MAP& map, ANAMY& anamy) {
	char op = 0;
	do {
		// 敌军操作
		anamy.autoMoving(map);
		// 子弹移动,不获取键盘事件也会移动
		this->attack(map, anamy);
		
		// 移动和开炮命令必须要获取键盘事件
		if (_kbhit()) {
			op = _getch();
			// 擦除坦克
			this->wipeTank(map);
			switch (op) {
				// 向上
				case UP: {
					this->setUP();
					// 判定是否为障碍物、河流、家，是则不能穿过
					if (map.getAllSth()[pos[1].getX()][pos[1].getY() - 1] == OBSTACLE || map.getAllSth()[pos[1].getX() - 1][pos[1].getY()] == OBSTACLE || map.getAllSth()[pos[1].getX() + 1][pos[1].getY()] == OBSTACLE || 
						map.getAllSth()[pos[1].getX()][pos[1].getY() - 1] == RIVER || map.getAllSth()[pos[1].getX() - 1][pos[1].getY()] == RIVER || map.getAllSth()[pos[1].getX() + 1][pos[1].getY()] == RIVER ||
						map.getAllSth()[pos[1].getX()][pos[1].getY() - 1] == HOME || map.getAllSth()[pos[1].getX() - 1][pos[1].getY()] == HOME || map.getAllSth()[pos[1].getX() + 1][pos[1].getY()] == HOME ||
						map.getAllSth()[pos[1].getX()][pos[1].getY() - 1] == FLAG || map.getAllSth()[pos[1].getX() - 1][pos[1].getY()] == FLAG || map.getAllSth()[pos[1].getX() + 1][pos[1].getY()] == FLAG ||
						map.getAllSth()[pos[1].getX() - 1][pos[1].getY()] == GLASS || map.getAllSth()[pos[1].getX() + 1][pos[1].getY()] == GLASS
						) {
					}
					// 只有头碰到草地才会进去，否则会被卡住
					else if (map.getAllSth()[pos[1].getX()][pos[1].getY() - 1] == GLASS) {
						// 设为隐身
						this->setStealth(true);
						this->wipeTank(map);
					}
					else {
						for (int i = 0; i < 6; i++) {
							int ty = pos[i].getY();
							pos[i].setY(--ty);
						}
						this->setStealth(false);
					}
					break;
				}
				// 向下
				case DOWN: {
					setDOWN();
					// 判定是否为障碍物、河流、家，是则不能穿过
					if (map.getAllSth()[pos[1].getX()][pos[1].getY() + 1] == OBSTACLE || map.getAllSth()[pos[1].getX() - 1][pos[1].getY()] == OBSTACLE || map.getAllSth()[pos[1].getX() + 1][pos[1].getY()] == OBSTACLE ||
						map.getAllSth()[pos[1].getX()][pos[1].getY() + 1] == RIVER || map.getAllSth()[pos[1].getX() - 1][pos[1].getY()] == RIVER || map.getAllSth()[pos[1].getX() + 1][pos[1].getY()] == RIVER ||
						map.getAllSth()[pos[1].getX()][pos[1].getY() + 1] == HOME || map.getAllSth()[pos[1].getX() - 1][pos[1].getY()] == HOME || map.getAllSth()[pos[1].getX() + 1][pos[1].getY()] == HOME ||
						map.getAllSth()[pos[1].getX()][pos[1].getY() + 1] == FLAG || map.getAllSth()[pos[1].getX() - 1][pos[1].getY()] == FLAG || map.getAllSth()[pos[1].getX() + 1][pos[1].getY()] == FLAG || 
						map.getAllSth()[pos[1].getX() - 1][pos[1].getY()] == GLASS || map.getAllSth()[pos[1].getX() + 1][pos[1].getY()] == GLASS
						) {
					}
					// 只有头碰到草地才会进去，否则会被卡住
					else if (map.getAllSth()[pos[1].getX()][pos[1].getY() + 1] == GLASS) {
						// 设为隐身
						this->setStealth(true);
						this->wipeTank(map);
					}
					else {
						for (int i = 0; i < 6; i++) {
							int ty = pos[i].getY();
							pos[i].setY(++ty);
						}
						this->setStealth(false);
					}
					break;
				}
				// 向左
				case LEFT: {
					setLEFT();
					// 判定是否为障碍物、河流、家，是则不能穿过
					if (map.getAllSth()[pos[1].getX() - 1][pos[1].getY()] == OBSTACLE || map.getAllSth()[pos[1].getX()][pos[1].getY() - 1] == OBSTACLE || map.getAllSth()[pos[1].getX()][pos[1].getY() + 1] == OBSTACLE ||
						map.getAllSth()[pos[1].getX() - 1][pos[1].getY()] == RIVER || map.getAllSth()[pos[1].getX()][pos[1].getY() - 1] == RIVER || map.getAllSth()[pos[1].getX()][pos[1].getY() + 1] == RIVER ||
						map.getAllSth()[pos[1].getX() - 1][pos[1].getY()] == HOME || map.getAllSth()[pos[1].getX()][pos[1].getY() - 1] == HOME || map.getAllSth()[pos[1].getX()][pos[1].getY() + 1] == HOME ||
						map.getAllSth()[pos[1].getX() - 1][pos[1].getY()] == FLAG || map.getAllSth()[pos[1].getX()][pos[1].getY() - 1] == FLAG || map.getAllSth()[pos[1].getX()][pos[1].getY() + 1] == FLAG ||
						map.getAllSth()[pos[1].getX()][pos[1].getY() - 1] == GLASS || map.getAllSth()[pos[1].getX()][pos[1].getY() + 1] == GLASS
						) {
					}
					// 只有头碰到草地才会进去，否则会被卡住
					else if (map.getAllSth()[pos[1].getX() - 1][pos[1].getY()] == GLASS) {
						// 设为隐身
						this->setStealth(true);
						this->wipeTank(map);
					}
					else {
						for (int i = 0; i < 6; i++) {
							int tx = pos[i].getX();
							pos[i].setX(--tx);
						}
						this->setStealth(false);
					}
					break;
				}
				// 向右
				case RIGHT: {
					setRIGHT();
					// 判定是否为障碍物、河流、家，是则不能穿过
					if (map.getAllSth()[pos[1].getX() + 1][pos[1].getY()] == OBSTACLE || map.getAllSth()[pos[1].getX()][pos[1].getY() - 1] == OBSTACLE || map.getAllSth()[pos[1].getX()][pos[1].getY() + 1] == OBSTACLE ||
						map.getAllSth()[pos[1].getX() + 1][pos[1].getY()] == RIVER || map.getAllSth()[pos[1].getX()][pos[1].getY() - 1] == RIVER || map.getAllSth()[pos[1].getX()][pos[1].getY() + 1] == RIVER ||
						map.getAllSth()[pos[1].getX() + 1][pos[1].getY()] == HOME || map.getAllSth()[pos[1].getX()][pos[1].getY() - 1] == HOME || map.getAllSth()[pos[1].getX()][pos[1].getY() + 1] == HOME ||
						map.getAllSth()[pos[1].getX() + 1][pos[1].getY()] == FLAG || map.getAllSth()[pos[1].getX()][pos[1].getY() - 1] == FLAG || map.getAllSth()[pos[1].getX()][pos[1].getY() + 1] == FLAG ||
						map.getAllSth()[pos[1].getX()][pos[1].getY() - 1] == GLASS || map.getAllSth()[pos[1].getX()][pos[1].getY() + 1] == GLASS
						) {
					}
					// 只有头碰到草地才会进去，否则会被卡住
					else if (map.getAllSth()[pos[1].getX() + 1][pos[1].getY()] == GLASS) {
						// 设为隐身
						this->setStealth(true);
						this->wipeTank(map);
					}
					else {
						for (int i = 0; i < 6; i++) {
							int tx = pos[i].getX();
							pos[i].setX(++tx);
						}
						this->setStealth(false);
					}
					break;
				}
				// 开炮
				case ATTACK: {
					if (bullet.getBAlive() == false) {
						// 子弹和一号格子同步
						bullet.setX(pos[1].getX());
						bullet.setY(pos[1].getY());

						// 子弹设为存在
						bullet.setBAlive(true);
						// 设定计时器
						bullet.setCClock();

						// 取出子弹坐标
						int ty = bullet.getY();
						int tx = bullet.getX();
						// 获取坦克当前方向
						char tdir = this->getDir();
						switch (tdir) {
						case UP: {
							// 子弹向上运动
							bullet.setY(--ty);
							bullet.setBDir(UP);
							// 还原上一个河流节点
							if (bullet.getLastLand() == RIVER) {
								map.setAllSth(tx, ty + 1, RIVER);
								PrintChar(tx, ty + 1, "≈", BLUE);
							}
							// 还原上一个草丛节点
							if (bullet.getLastLand() == GLASS) {
								map.setAllSth(tx, ty + 1, GLASS);
								PrintChar(tx, ty + 1, "@", GREEN);
							}
							break;
						}
						case DOWN: {
							// 子弹向下运动
							bullet.setY(++ty);
							bullet.setBDir(DOWN);
							// 还原上一个河流节点
							if (bullet.getLastLand() == RIVER) {
								map.setAllSth(tx, ty - 1, RIVER);
								PrintChar(tx, ty - 1, "≈", BLUE);
							}
							// 还原上一个草丛节点
							if (bullet.getLastLand() == GLASS) {
								map.setAllSth(tx, ty - 1, GLASS);
								PrintChar(tx, ty - 1, "@", GREEN);
							}
							break;
						}
						case LEFT: {
							// 子弹向左运动							
							bullet.setX(--tx);
							bullet.setBDir(LEFT);
							// 还原上一个河流节点
							if (bullet.getLastLand() == RIVER) {
								map.setAllSth(tx + 1, ty, RIVER);
								PrintChar(tx + 1, ty, "≈", BLUE);
							}
							// 还原上一个草丛节点
							if (bullet.getLastLand() == GLASS) {
								map.setAllSth(tx + 1, ty, GLASS);
								PrintChar(tx + 1, ty, "@", GREEN);
							}
							break;
						}
						case RIGHT: {
							// 子弹向右运动
							bullet.setX(++tx);
							bullet.setBDir(RIGHT);
							// 还原上一个河流节点
							if (bullet.getLastLand() == RIVER) {
								map.setAllSth(tx - 1, ty, RIVER);
								PrintChar(tx - 1, ty, "≈", BLUE);
							}
							// 还原上一个草丛节点
							if (bullet.getLastLand() == GLASS) {
								map.setAllSth(tx - 1, ty, GLASS);
								PrintChar(tx - 1, ty, "@", GREEN);
							}
							break;
						}
						default:
							break;
						}
						// 判定子弹碰撞
						if (map.getAllSth()[tx][ty] == SPACE) {
							bullet.setLastLand(SPACE);
						}
						else if (map.getAllSth()[tx][ty] == OBSTACLE) {
							bullet.setBAlive(false);
						}
						else if (map.getAllSth()[tx][ty] == HOME) {
							this->wipeBullet(map);
							bullet.setBAlive(false);
							map.setAllSth(tx, ty, SPACE);
						}
						else if (map.getAllSth()[tx][ty] == RIVER) {
							bullet.setLastLand(RIVER);
						}
						else if (map.getAllSth()[tx][ty] == GLASS) {
							bullet.setLastLand(GLASS);
						}
						else if (map.getAllSth()[tx][ty] == TANKOT) {
							bullet.setBAlive(false);
							anamy.setTAlive(false);
						}
						break;
					}
				}
				default:
					break;
			}
			// 不隐身才打印
			if (this->getStealth() == false) {
				this->showTank(map);
			}
		}	
	} while (true);
}

// 获取子弹情况
BULLET TANK::getBullet() {
	return this->bullet;
}

// 获取坦克的存活情况
bool TANK::getTAlive() {
	return this->talive;
}

// 设置坦克存活
void TANK::setTAlive(bool _flag) {
	this->talive = _flag;
}
