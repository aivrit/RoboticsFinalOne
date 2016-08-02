/*
 * WaypointsManger.cpp
 *
 *  Created on: Jun 21, 2015
 *      Author: colman
 */

#include "WaypointsManager.h"

using namespace std;

WaypointsManager::WaypointsManager(int w, int h, double r){
	WidthMap = w;
	HeightMap = h;
	resoultion = r;
}

WaypointsManager::~WaypointsManager() {
	// TODO Auto-generated destructor stub
}

// Creates the waypoint from the path, a way point will be created in a corner or every 4 cells of the map
Waypoint* WaypointsManager::createWaypoints(vector<Location*> LocationArray)
{
	int numberOfCells = 0;
	int* currentWay;
	Waypoint* firstWaypoint;
	Waypoint* waypoint;

	// First way point will be the first cell of the path
	waypoint = new Waypoint(LocationArray[0]->col, LocationArray[0]->row);
	firstWaypoint = waypoint;
	currentWay = getWay(LocationArray[0], LocationArray[1]);



	// Go over all the Locations
	for (int i = 1; i < LocationArray.size() - 1; i++)
	{
		int* nextWay = getWay(LocationArray[i], LocationArray[i + 1]);

		// Check if the way is changed (corner). Also check if it is the fourth Location
		if (currentWay[0] !=  nextWay[0] || currentWay[1] != nextWay[1] || numberOfCells == 4)
		{
			waypoint->nextWaypoint = new Waypoint(LocationArray[i]->col, LocationArray[i]->row);
			waypoint = waypoint->nextWaypoint;
			numberOfCells = 0;
		}

		numberOfCells++;
		currentWay = nextWay;
	}




	// The last Location of the path is a waypoint
	waypoint->nextWaypoint = new Waypoint(LocationArray[LocationArray.size() - 1]->col,
			LocationArray[LocationArray.size() - 1]->row);

	return firstWaypoint;
}

int* WaypointsManager::getWay(Location* current, Location* next)
{
	int* way = new int[2];
	way[0] = current->row - next->row;
	way[1] = current->col - next ->col;

	return way;
}

float WaypointsManager::getXFromCol(int col)
{
	return col/4;
}

float WaypointsManager::getYFromRow(int row)
{
	return row/4;
}
