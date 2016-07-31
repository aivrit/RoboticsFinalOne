#include "Robot.h"

using namespace std;

double Robot::getLaserScan(int index)
{
	return _lp[index];
}

void Robot::Read()
{
	_pc.Read();
}

void Robot::setSpeed(double linearSpeed, double angularSpeed)
{
	_pp.SetSpeed(linearSpeed,angularSpeed);
}

void Robot::setOdometry(double x, double y, double yaw)
{
	cout << x << "," << y << "," << yaw << endl;

	_pp.SetOdometry(x,y,yaw);
}

double Robot::getXPos()
{

	return ((_pp.GetXPos() * 10 )-37);
}

double Robot::getYPos()
{
	return ((_pp.GetYPos() * -10) + 6);
}

double Robot::getYaw()
{
	double currYaw;
	if (_pp.GetYaw() > PI)
	{
		currYaw = (_pp.GetYaw() - 2*PI) * 180 / PI;
	}
	else{
		currYaw = _pp.GetYaw() *  180 / PI;
	}
	return currYaw;
}

Robot::~Robot()
{
	delete &_pc;
	delete &_pp;
	delete &_lp;
}
