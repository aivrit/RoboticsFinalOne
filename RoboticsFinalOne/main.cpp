/*
 * main.cpp
 *
 *      Author: Alon
 *
 */

#include <iostream>
#include <cmath>
#include "pngUtil.h"
#include "GuiConnectionManager.h"
#include <libplayerc++/playerc++.h>

using namespace std;
using namespace PlayerCc;


int main() {

	PlayerClient* _pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;


	thickenMap("roboticLabMap.png",  3);
	std::cout << "did it" << endl;

	GuiConnectionManager* c = new GuiConnectionManager();
	c->conn("192.168.1.21", 10000);
	c->send_data("add,100,100,106,106,112,100,a");
}


