#ifndef MANAGER_H_
#define MANAGER_H_
#include "Models/Robot.h"
#include "Map/Map.h"
#include "LocalizationManager.h"
#include "A-Star/AStar.h"
#include "Waypoints/WaypointsManager.h"

// Noise to simulate real world wrong reads.
#define NOISE_Location_FACTOR 0.02
#define NOISE_YAW_FACTOR 0.01

class Manager {

	Robot* _Robot;
	Waypoint* _nextWaypoint;
	Map* _map;
	LocalizationManager* _slam;
	double _RobotStartPosX;
	double _RobotStartPosY;
	double _RobotYaw;

public:
	Manager(Robot* robot, LocalizationManager* slam, Waypoint* firstWaypoint, Map* map, double RobotStartPosX,double RobotStartPosY, double RobotYaw);
	virtual ~Manager();
	void run();
	bool isReachedWaypoint();

};

#endif /* MANAGER_H_ */
