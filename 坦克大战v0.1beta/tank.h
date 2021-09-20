#pragma once
#include "map.h"
#include "node.h"

// 宏定义区
#define UP     'w'
#define DOWN   's'
#define LEFT   'a'
#define RIGHT  'd'
#define ATTACK 'j'

// 子弹类 继承自节点类
class BULLET:public NODE {
private:
	int speed;                    // 速度
	int cclock;                   // 时钟
	char bdir;                    // 方向
	bool balive;                  // 是否存在
	int lastland;                 // 上一个地形
public:
	BULLET(MAP& map);             // 构造函数
	void setSpeed(int _speed);    // 设置速度
	int getSpeed();
	void setCClock();             // 设置时钟
	int getCClock();
	void setBDir(char _tdir);     // 设置方向
	char getBDir();               // 获取方向
	void setBAlive(bool alive);   // 设置是否存在
	bool getBAlive();             // 获取存在情况
	void setLastLand(int _land);  // 设置上一个地形
	int getLastLand();            // 获取上一个地形
};

class ANAMY;

// 坦克类
class TANK {
private:
	NODE pos[6];                      // 坦克的身体
	char direction = UP;              // 初始方向为上
	BULLET bullet;                    // 子弹
	bool stealthl;                    // 隐身状态
	bool talive;                      // 存活            
public:
	TANK(MAP& map);                        // 构造函数
	// ~TANK();                            // 析构函数
	NODE* getPos();                        // 获取坦克身体节点
	void setDir(char _tdir);               // 设置方向
	char getDir();
	void setUP();                          // 设置向上形态
	void setDOWN();                        // 设置向下形态
	void setLEFT();                        // 设置向左形态
	void setRIGHT();                       // 设置向右形态
	void attack(MAP& map, ANAMY& anamy);   // 攻击
	void opTank(MAP& map, ANAMY& anamy);   // 操作坦克
	virtual void showTank(MAP& map);       // 遍历打印坦克
	void showBullet(MAP& map);             // 打印子弹
	void wipeBullet(MAP& map);             // 擦除子弹
	void wipeTank(MAP& map);               // 擦除坦克
	void setStealth(bool _flag);           // 设置隐身
	bool getStealth();                     // 获取隐身状态
	BULLET getBullet();                    // 获取子弹情况
	void setTAlive(bool _flag);            // 设置坦克存活
	bool getTAlive();                      // 获取坦克存活
};

// 敌军坦克类，继承自坦克类
class ANAMY :public TANK {
private:
	int aclock;                            // 敌军坦克时钟
	int aspeed;                            // 敌军运动速度
	int adir;                              // 敌军坦克方向
public:
	ANAMY(MAP& map);                       // 敌军构造
	//~ANAMY();                            // 敌军析构
	void setAClock();                      // 设定时钟
	int getAClock();                       // 获取时钟
	void showTank(MAP& map);               // 画坦克
	void autoMoving(MAP& map);             // 自动移动
	void autoShooting(MAP& map);           // 自动射击
	int getASpeed();                       // 获取移动速度
	void setADir(int _dir);                // 设定敌军方向
	int getADir();                         // 获取敌军坦克方向
};