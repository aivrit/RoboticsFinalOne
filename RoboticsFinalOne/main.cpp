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
#include "RobotParams.h"
#include "Global.h"
#include <libplayerc++/playerc++.h>

using namespace std;
using namespace PlayerCc;


int main() {

	RobotParams* p = RobotParams::Instance();

	PlayerClient* _pc = new PlayerClient("localhost", 6665);
	Position2dProxy* _pp = new Position2dProxy(_pc);
	LaserProxy* _lp = new LaserProxy(_pc);


	thickenMap("roboticLabMap.png",  3);
	std::cout << "did it" << endl;

	GuiConnectionManager* c = new GuiConnectionManager();
	//c->conn("192.168.1.21", 10000);
	//c->send_data("add,100,100,106,106,112,100,a");

	_pp->SetOdometry(-6.009, 2.481, dtor(-194.220));

	while (true)
	{
		_pc->Read();

		for (int i=0; i< _lp->GetCount(); i++)
		{
			cout << _lp->GetRange(i) << endl;
		}
	}
}


