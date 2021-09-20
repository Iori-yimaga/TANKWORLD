#include "node.h"

// 节点类构造
NODE::NODE() {
	this->setX(0);
	this->setY(0);
}

// 设置横坐标
void NODE::setX(int _x) {
	this->x = _x;
}

//获取横坐标
int NODE::getX() {
	return this->x;
}

// 设置纵坐标
void NODE::setY(int _y) {
	this->y = _y;
}

// 获取纵坐标
int NODE::getY() {
	return this->y;
}