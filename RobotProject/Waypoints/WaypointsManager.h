/*
 * WaypointsManger.h
 *
 *  Created on: Jun 21, 2015
 *      Author: colman
 */

#ifndef WAYPOINTSMANGER_H_
#define WAYPOINTSMANGER_H_

#include "../Location.h"
#include "Waypoint.h"
#include "stdlib.h"
#include <vector>

using namespace std;

class WaypointsManager {
private:
	int WidthMap;
	int HeightMap;
	double resoultion;
public:
	WaypointsManager(int w, int h, double r);
	virtual ~WaypointsManager();
	Waypoint* createWaypoints(vector<Location*> LocationArray);
	int* getWay(Location* current, Location* next);
	float getXFromCol(int col);
	float getYFromRow(int row);
};

#endif /* WAYPOINTSMANGER_H_ */
