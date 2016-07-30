#include "Particle.h"
#include <math.h>

Particle::Particle(double x, double y, double pYaw, double bel, Map* map) : _xPos(x), _yPos(y), _yaw(pYaw), _belief(bel)
{
	_map = new Map(map);
}

Map* Particle::getMap()
{
	return _map;
}

double Particle::getBelief()
{
	return _belief;
}

void Particle::update(double deltaX, double deltaY, double deltaYaw, Robot* robot)
{

	_xPos += deltaX;
	_yPos += deltaY;

	if(_xPos < 10 && _yPos < 10)
	{
		_xPos =  _xPos * 10;
		_yPos = _yPos * -10;
	}

	_yaw += deltaYaw;

	// Get the predicted belief
	double predictedBelief = _belief * calcNewLocationProbability(deltaX, deltaY, deltaYaw);
	// Get the observations probability
	double obsProb = calcObservationsAccuracy(robot);

	// Calculate new belief - according to the predicted belief and observations
	_belief = NORMALIZE_FACTOR * predictedBelief * obsProb;

	if (_belief > 1)
		_belief = 1;
}

double Particle::calcNewLocationProbability(double deltaX, double deltaY, double deltaYaw)
{
	// Calculate the distance passed from the previous location
	double distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

	// If the robot did not change its orientation and did not move more than the threshold,
	// we are fully sure.
	if ((deltaYaw == 0) && (distance < DIS_THRESHOLD))
	{
		return 1;
	}
	// If the robot did not change its orientation more than the threshold
	// and did not move more than the threshold, we are almost sure.
	else if ((distance < DIS_THRESHOLD) && (deltaYaw < YAW_ANGLE_THRESHOLD))
	{
		return 0.8;
	}
	// If the robot did not change its orientation more than the threshold
	// or it did not move more than the threshold, we are not so sure.
	else if (((distance > DIS_THRESHOLD) && (deltaYaw < YAW_ANGLE_THRESHOLD)) ||
			 ((distance < DIS_THRESHOLD) && (deltaYaw > YAW_ANGLE_THRESHOLD)))
	{
		return 0.5;
	}
	// If the robot changed its orientation more than the threshold
	// and it moved more than the threshold, we are not sure about the robot's location.
	else
	{
		return 0.2;
	}
}

double Particle::calcObservationsAccuracy(Robot* robot)
{
	double numOfWrongMapCells = 0;
	double numOfRightMapCells = 0;

	for (int i=0; i< MAX_LASER_INDEX; i+=5)
	{
		double laserAngle = laserIndexToLaserAngle(i);
		double disFromObstacle = robot->getLaserScan(i);

		double obstacleXPos = _xPos + (disFromObstacle * cos((_yaw + laserAngle) / 180 * PI));
		double obstacleYPos = _yPos + (disFromObstacle * sin((_yaw + laserAngle) / 180 * PI));
	//	obstacleXPos = obstacleXPos;
		//obstacleYPos = obstacleYPos * -10;

		// Get the value in the map's cell that represents the obstacle location
		char obstacleCurrCellValue = _map->getMapValueFromRealLocation(obstacleXPos, obstacleYPos);

		// if the distance is too large, assume that there is no obstacle in this index and don't update the map
		// and if the distance is too short don't consider it as an obstacle because its the robot itself
		if (disFromObstacle < 4.0 && disFromObstacle > 0.2)
		{
			int row1;
			int col1;
			switch (obstacleCurrCellValue)
			{
				case 'p':
				case 'A':
				case 'B':
				case 'W':
				case 'P':
				case 'R':
				case FREE_CELL:
					numOfWrongMapCells ++;
					_map->setMapValueFromRealLocation(obstacleXPos, obstacleYPos, BLOCK_CELL);
					row1 = _map->getRowFromYPos(obstacleYPos);
					col1 = _map->getColFromXPos(obstacleXPos);
					for (int i1 = row1 - 2; i1 <= row1 + 2; i1++)
					{
						for (int j = col1- 2; j <= col1 + 2; j++)
						{
							_map->setMapValue(i1, j, BLOCK_CELL);
						}
					}
					break;
				case BLOCK_CELL:
					numOfRightMapCells ++;
					break;
				default:
					break;
			}
		}

		freeCellsToObstacle(obstacleXPos, obstacleYPos, disFromObstacle);
	}

	// Set free in the particle's position
	_map->setMapValueFromRealLocation(_xPos, _yPos, FREE_CELL);

	return numOfWrongMapCells == 0 ? 1 : (numOfRightMapCells / (numOfRightMapCells + numOfWrongMapCells));
}

void Particle::freeCellsToObstacle(double obstacleXPos, double obstacleYPos, double distanceToObstacle)
{
	//double xDifference = obstacleXPos - _xPos ;
	//double yDifference = obstacleYPos - _yPos;
	double xDifference = obstacleXPos - _xPos;
	double yDifference = obstacleYPos - _yPos;
	double angleToObstacle = atan(yDifference / xDifference);

	double xProgressRatio = abs(cos(angleToObstacle));
	if (obstacleXPos < _xPos)
	//if (obstacleXPos < _xPos)
	{
		xProgressRatio = -xProgressRatio;
	}

	double yProgressRatio = abs(sin(angleToObstacle));
	if (obstacleYPos < _yPos)
//	if (obstacleYPos < _yPos)
	{
		yProgressRatio = -yProgressRatio;
	}

	// Set free cells in the free space between the robot and the obstacle
	for (double j=0; j < distanceToObstacle; j++)
	{
	//	_map->setMapValueFromRealLocation(_xPos + j*xProgressRatio, _yPos+ j*yProgressRatio, FREE_CELL);
	_map->setMapValueFromRealLocation(_xPos + j*xProgressRatio, _yPos + j*yProgressRatio, FREE_CELL);
	}
}

double Particle::laserIndexToLaserAngle(int index)
{
	return (index * 0.36) - 120; /// 180.0) * PI;
}

Particle* Particle::createNewParticle()
{
	double angle = (rand() % 360) * PI / 180.0;
	double yawAngle = (rand() % NEW_PARTICLE_ANGLE_LIMIT - 30.0); //* PI / 180.0;

	double newX = _xPos + cos(angle) * NEW_PARTICLE_RADIUS;
	//newX = newX * 10;

	double newY = _yPos+ sin(angle) * NEW_PARTICLE_RADIUS;
	//newY = newY * -10;


	double newYaw = _yaw + yawAngle;




	if (_map->getColFromXPos(newX) < 0 || _map->getRowFromYPos(newY) < 0 ||
			_map->getRowFromYPos(newY) >= _map->getMapHeight() || _map->getColFromXPos(newX) >= _map->getMapWidth())
	{
		return NULL;
	}

	Map* newMap = new Map(_map)	;
	return new Particle(newX, newY, newYaw, _belief, newMap);
}

double Particle::getX()
{
	//return _xPos;
	return _xPos ;
}
double Particle::getY()
{
	//return _yPos;
	return  _yPos ;
}
double Particle::getYaw()
{
	return _yaw;
}

Particle::~Particle()
{
	delete _map;
}
