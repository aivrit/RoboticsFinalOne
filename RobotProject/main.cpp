/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */
// Michael Lefkovits $ Alon Bar-tzlil
#include <libplayerc++/playerc++.h>
#include "ConfigurationManager.h"
#include "MapLoader/MapLoader.h"
#include "A-Star/AStar.h"
#include "Waypoints/Waypoint.h"
#include "Waypoints/WaypointsManager.h"
#include "Manager.h"
#include "Models/Robot.h"


using namespace PlayerCc;


int main() {

	// Init map
	ConfigurationManager config("/home/colman/git/RoboticsFInalOne/RobotProject/Config/parameters.txt");
	Map map = CreateMap(config);

	// Put robot on map
	double* robotStartLocation = config.getStartLocation();
	//map.setMapValueFromRealLocation(robotStartLocation[0], robotStartLocation[1], ROBOT_CELL);

	// Put goal on map
	double* goalLocation = config.getGoal();
	//map.setMapValueFromRealLocation(goalLocation[0], goalLocation[1], GOAL_CELL);

	AStar* astar = new AStar(&map);

	vector<Position*> path = astar->findPath(robotStartLocation[1]/4,
												 robotStartLocation[0]/4,
												 goalLocation[1]/4,
												 goalLocation[0]/4);


	for(int i = 0; i < path.size(); i++)
	{
		map.setMapValue(path[i]->row, path[i]->col, 'P');
	}


	map.setMapValue(robotStartLocation[1]/4, robotStartLocation[0]/4, 'R');
	map.setMapValue(goalLocation[1]/4, goalLocation[0]/4, 'E');

	map.printMap();

	// Create waypoints
	double x = config.getGridResolutionCM();
	x = x / 100;
	WaypointsManager waypointsManager(map.getMapWidth(), map.getMapHeight(), x);
	Waypoint* startWaypoint = waypointsManager.createWaypoints(path);
	Waypoint* firstRealWaypoint = startWaypoint;

	// Robot
	Robot robot("10.10.245.63",6665);

	robot.setOdometry(robotStartLocation[0]/40, robotStartLocation[1]/-40, robotStartLocation[2] / 180 * PI);

		LocalizationManager* slam = new LocalizationManager(&robot, map.getMapHeight(), map.getMapWidth(), map.getMapResolution());
		slam->setRobot(&robot);


		slam->initFirstParticle(&map,robotStartLocation[0]/40, robotStartLocation[1]/-40, robotStartLocation[2]);

		Manager manager(&robot, slam, firstRealWaypoint, &map, robotStartLocation[0]/4, robotStartLocation[1]/4, robotStartLocation[2]);
		manager.run();

	return 0;

}
