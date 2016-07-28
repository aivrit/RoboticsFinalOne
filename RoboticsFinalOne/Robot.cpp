/*
 * Robot.cpp
 *
 *  Created on: Jun 25, 2016
 *      Author: colman
 */

#include "Global.h"
#include "Robot.h"

Robot::Robot(char* host, int port)
{
	this->_pc = new PlayerClient(host, port);
	this->_lp = new LaserProxy(this->_pc);
	this->_pp = new Position2dProxy(this->_pc);
	this->_laserRanges = new double[MAX_LASER_RANGE];
	this->_loc->x = this->_pp->
}

double* Robot::GetLaserRanges()
{
	for(int i=0; i<MAX_LASER_RANGE;i+=20)
	{
		this->_laserRanges[i] = this->_lp->GetRange(i);
	}

	return this->_laserRanges;
}

