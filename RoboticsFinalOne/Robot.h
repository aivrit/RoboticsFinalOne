/*
 * Robot.h
 *
 *  Created on: Jun 25, 2016
 *      Author: colman
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <iostream>
#include <cmath>
#include "pngUtil.h"
#include "GuiConnectionManager.h"
#include <libplayerc++/playerc++.h>

using namespace std;
using namespace PlayerCc;

class Robot
{

	//Data Members
	public:
		PlayerClient*    _pc;
		Position2dProxy* _pp;
		LaserProxy*      _lp;
		Location*         _loc;
	private:
		double*          _laserRanges;

	//Methods
	Robot(char* host, int port);

	public:
		double* GetLaserRanges();


};



#endif /* ROBOT_H_ */
