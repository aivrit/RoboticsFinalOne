/*
 * Waypoint.cpp
 *
 *  Created on: Jun 21, 2015
 *      Author: colman
 */

#include "Waypoint.h"

Waypoint::Waypoint(float x, float y) {
	this->x =  x;
	this->y = y;
	this->nextWaypoint = NULL;
}

float Waypoint::getX() {
	return x;
}

float Waypoint::getY() {
	return y;
}

Waypoint::~Waypoint() {
	// TODO Auto-generated destructor stub
}
