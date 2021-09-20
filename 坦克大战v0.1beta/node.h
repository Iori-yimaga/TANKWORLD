#pragma once

// 节点类
class NODE {
private:
	int x;                       // 横坐标
	int y;                       // 纵坐标
public:
	NODE();                      // 构造函数
	void setX(int _x);           // 设置横坐标
	int getX();
	void setY(int _y);           // 设置纵坐标
	int getY();
};