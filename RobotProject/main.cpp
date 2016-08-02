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
#include "AStar.h"
#include "Waypoints/Waypoint.h"
#include "Waypoints/WaypointsManager.h"
#include "Manager.h"
#include "Robot.h"


using namespace PlayerCc;


int main() {

	// Init map
	ConfigurationManager config("/home/colman/git/RoboticsFInalOne/RobotProject/Config/parameters.txt");
	Map map = CreateMap(config);

	// Put robot on map
	double* robotStartLocation = config.getStartLocation();

	// Put goal on map
	double* goalLocation = config.getGoal();

	AStar* astar = new AStar(&map);

	vector<Location*> path = astar->findPath(robotStartLocation[1]/4,
												 robotStartLocation[0]/4,
												 goalLocation[1]/4,
												 goalLocation[0]/4);


	// Create waypoints
	double gridResMeters = config.getGridResolutionCM() / 100;
	WaypointsManager waypointsManager(map.getMapWidth(), map.getMapHeight(), gridResMeters);
	Waypoint* startWaypoint = waypointsManager.createWaypoints(path);

	// Robot
	Robot robot("localhost",6665);

	robot.setOdometry(robotStartLocation[0]/40, robotStartLocation[1]/-40, robotStartLocation[2] / 180 * PI);

		LocalizationManager* lm = new LocalizationManager(&robot, map.getMapHeight(), map.getMapWidth(), map.getMapResolution());
		lm->setRobot(&robot);


		lm->initFirstParticle(&map,robotStartLocation[0]/40, robotStartLocation[1]/-40, robotStartLocation[2]);

		Manager manager(&robot, lm, startWaypoint, &map, robotStartLocation[0]/4, robotStartLocation[1]/4, robotStartLocation[2]);
		manager.run();

	return 0;

}
