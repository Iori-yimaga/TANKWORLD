#include "game.h"
#include "map.h"
#include "tank.h"
#include <iostream>

int main() {
	MAP map;
	TANK ta(map);
	ANAMY ay(map);
	ta.opTank(map, ay);	
    return 0;
}
