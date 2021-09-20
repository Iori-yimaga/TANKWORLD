#include "map.h"
#include "game.h"

// 初始化地图
MAP::MAP() {
	// 地图边界的标记
	for (int i = 0; i < MAP_X; i++) {
		for (int j = 0; j < MAP_Y; j++) {
			if (i == 0 || i == MAP_X - 1 || j == 0 || j == MAP_Y - 1) {
				this->allSth[i][j] = OBSTACLE;
			}
			else {
				this->allSth[i][j] = SPACE;
			}
		}
	}

	// 生成草地
	this->initGlass();
	// 生成河流
	this->initRiver();
	// 生成家
	this->initHome();
	// 生成flag
	this->initFlag();
	// 画地图
	this->drawMap();
}
// 析构函数
//MAP::~MAP() {
//	for (int i = 0; i < MAP_X; i++) {
//		delete[] allSth;
//	}
//	delete[] allSth;
//}
// 画地图
void MAP::drawMap() {
	for (int i = 0; i < MAP_X; i++) {
		for (int j = 0; j < MAP_Y; j++) {
			if (allSth[i][j] == OBSTACLE) {
				PrintChar(i, j, "■");
			}
			if (allSth[i][j] == GLASS) {
				PrintChar(i, j, "@", GREEN);
			}
			if (allSth[i][j] == RIVER) {
				PrintChar(i, j, "≈", BLUE);
			}
			if (allSth[i][j] == HOME) {
				PrintChar(i, j, "■", YELLOW);
			}
			if (allSth[i][j] == FLAG) {
				PrintChar(i, j, "囍", RED);
			}
		}
	}
}
// 返回坐标
int (*MAP::getAllSth())[MAP_Y] {
	return this->allSth;
}
// 设置标记
void MAP::setAllSth(int _x, int _y, int flag) {
	this->allSth[_x][_y] = flag;
}
// 生成河流
void MAP::initRiver() {
	// 第一个节点
	river[0].setX(25);
	river[0].setY(10);
	for (int i = 1; i < 10; i++) {
		river[i].setX(river[i - 1].getX() + 1);
		river[i].setY(river[i - 1].getY());
	}
	river[10].setX(river[0].getX());
	river[10].setY(river[0].getY() + 1);
	for (int i = 11; i < 20; i++) {
		river[i].setX(river[i - 1].getX() + 1);
		river[i].setY(river[i - 1].getY());
	}
	for (int i = 0; i < 20; i++) {
		allSth[river[i].getX()][river[i].getY()] = RIVER;
	}
}
// 生成草地
void MAP::initGlass() {
	// 第一个节点
	glass[0].setX(35);
	glass[0].setY(10);
	for (int i = 1; i < 3; i++) {
		glass[i].setX(glass[i - 1].getX() + 1);
		glass[i].setY(glass[i - 1].getY());
	}
	glass[3].setX(glass[0].getX());
	glass[3].setY(glass[0].getY() + 1);
	for (int i = 4; i < 6; i++) {
		glass[i].setX(glass[i - 1].getX() + 1);
		glass[i].setY(glass[i - 1].getY());
	}
	glass[6].setX(22);
	glass[6].setY(10);
	for (int i = 7; i < 9; i++) {
		glass[i].setX(glass[i - 1].getX() + 1);
		glass[i].setY(glass[i - 1].getY());
	}
	glass[9].setX(glass[6].getX());
	glass[9].setY(glass[6].getY() + 1);
	for (int i = 10; i < 12; i++) {
		glass[i].setX(glass[i - 1].getX() + 1);
		glass[i].setY(glass[i - 1].getY());
	}
	for (int i = 0; i < 12; i++) {
		allSth[glass[i].getX()][glass[i].getY()] = GLASS;
	}
}
// 生成家
void MAP::initHome() {
	// 第一个节点
	home[0].setX(30);
	home[0].setY(27);
	home[1].setX(home[0].getX() - 1);
	home[1].setY(home[0].getY());
	home[2].setX(home[0].getX() + 1);
	home[2].setY(home[0].getY());
	home[3].setX(home[0].getX() - 1);
	home[3].setY(home[0].getY() + 1);
	home[4].setX(home[0].getX() + 1);
	home[4].setY(home[0].getY() + 1);
	for (int i = 0; i < 5; i++) {
		allSth[home[i].getX()][home[i].getY()] = HOME;
	}
}
// 生成flag
void MAP::initFlag() {
	flag.setX(30);
	flag.setY(28);
	allSth[flag.getX()][flag.getY()] = FLAG;
}
