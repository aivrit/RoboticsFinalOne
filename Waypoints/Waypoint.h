/*
 * Waypoint.h
 *
 *  Created on: Jun 21, 2015
 *      Author: colman
 */
#include <iostream>
#ifndef WAYPOINT_H_
#define WAYPOINT_H_

using namespace std;

class Waypoint {
private:
	float x;
	float y;
public:
	Waypoint(float x, float y);
	Waypoint* nextWaypoint;
	float getX();
	float getY();
	virtual ~Waypoint();
};

#endif /* WAYPOINT_H_ */
