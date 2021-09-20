#pragma once

#include "node.h"

#define MAP_X     60
#define MAP_Y     30

#define SPACE     0
#define OBSTACLE  1
#define TANKME    2
#define TANKOT    3
#define BULLETT   4
#define GLASS     5
#define RIVER     6
#define HOME      7
#define FLAG      8

class MAP {
private:
	int allSth[MAP_X][MAP_Y];                     // 二维数组
	NODE river[20];
	NODE glass[12];
	NODE home[5];
	NODE flag;
public:
	MAP();                                        // 构造函数
	//~MAP();                                      // 析构函数             
	void drawMap();                               // 画地图
	int(*getAllSth())[MAP_Y];                     // 获取数组
	void setAllSth(int _x, int _y, int flag);     // 设置标记
	void initRiver();                            // 画河流
	void initGlass();                            // 画草地
	void initHome();                             // 初始化家
	void initFlag();                             // 生成flag  
};
