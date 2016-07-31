#include "Manager.h"
#include <math.h>

Manager::Manager(Robot* robot, LocalizationManager* slam, Waypoint* firstWaypoint, Map* map, double RobotStartPosX,double RobotStartPosY, double RobotYaw )
{

	_Robot = robot;
	_nextWaypoint = firstWaypoint;
	_map = map;
	_slam = slam;
	_RobotStartPosX = RobotStartPosX;
	_RobotStartPosY = RobotStartPosY;
	_RobotYaw = RobotYaw;
}

double findRotationSide(double srcYaw, double dstYaw)
{
	double leftCost = 0, rightCost = 0;

	if(srcYaw > 0)
	{
		if(dstYaw >= 0 && dstYaw < srcYaw)
		{
			leftCost = 180 - 20 + 180 + dstYaw;
			rightCost = srcYaw - dstYaw;
		}
		else if(dstYaw >= 0 && dstYaw >= srcYaw)
		{
			leftCost = dstYaw - srcYaw;
			rightCost = srcYaw + 180 + (180 -dstYaw);
		}
		else if(dstYaw < 0)
		{
			leftCost = 180 - srcYaw + (180 + dstYaw);
			rightCost = srcYaw + (-1 * dstYaw);
		}

	}
	else
	{
		if(dstYaw <= 0 && dstYaw < srcYaw)
		{
			leftCost = (-1 * srcYaw) + 180 + dstYaw;
			rightCost = (-1 * dstYaw) + srcYaw;
		}
		else if(dstYaw <= 0 && dstYaw >= srcYaw)
		{
			leftCost = (-1 * srcYaw) + dstYaw;
			rightCost = 180 + srcYaw + 180 + (-1 * dstYaw);
		}
		else if(dstYaw > 0)
		{
			leftCost = (-1 * srcYaw) + dstYaw;
			rightCost = 180 + srcYaw + (180 - dstYaw);
		}
	}


	if(leftCost < rightCost)
	{
		return 0.1;
	}
	else
	{
		return -0.1;
	}
}

double findDegreeToRotate(double srcX, double srcY, double dstX, double dstY, double Yaw, LocalizationManager* slam)
{


	double linearX;
	double linearY;
	int yaw;


	if (slam == NULL)
	{
		linearX = dstX - srcX;
		linearY = -1 * (dstY - srcY);
		yaw = Yaw;
	}
	else
	{

		if (slam->getXOfBestParticle() < 10 && slam->getYOfBestParticle() < 10)
		{
			linearX = dstX - slam->getXOfBestParticle() * 10;
			linearY = -1 * (dstY - slam->getYOfBestParticle()* -10);
			yaw = Yaw;

		}
		else
		{
			linearX = dstX - (slam->getXOfBestParticle());
			linearY = -1 * (dstY - (slam->getYOfBestParticle()));
			yaw = slam->getYawOfBestParticle();
		}

	}


	int linearXint = linearX * 10000;
	int linearYint = linearY * 10000;



	double degreeRobotToWaypoint = atan2(linearYint, linearXint) *  180 / PI;


	return degreeRobotToWaypoint;
}

void Manager::run()
{
	//Hadar
	double mapSourceX, mapSourceY;
	double mapDestinationX, mapDestinationY;
	double dgre;
	bool firstW = true;
	double srcYaw;
	double rotationSide;
	double grace;

	for(int i = 0; i < 15; i++)
	{
		_Robot->Read();
	}

	double prevX = _Robot->getXPos(), prevY = _Robot->getYPos(), prevYaw = _Robot->getYaw();
	double newX, newY, newYaw;

	while (_nextWaypoint)
	{

		if (firstW)
		{
			 mapSourceX = _RobotStartPosX;
			 mapSourceY = _RobotStartPosY;
			 mapDestinationX = _nextWaypoint->getX();
			 mapDestinationY = _nextWaypoint->getY();
  			 firstW = false;
		}


		_Robot->Read();
		dgre = findDegreeToRotate(mapSourceX,mapSourceY,mapDestinationX,mapDestinationY,prevYaw, _slam);


		/////////// Particals part ////////


		// Get the robot's new location
		newX = _Robot->getXPos();
		newY = _Robot->getYPos();
		newYaw = _Robot->getYaw();

		// Use some noise to simulate real world wrong reads.
		newX = newX + ((double) rand() / (RAND_MAX)) * 2 * NOISE_Location_FACTOR - NOISE_Location_FACTOR;
		newY = newY + ((double) rand() / (RAND_MAX)) * 2 * NOISE_Location_FACTOR - NOISE_Location_FACTOR;
		//newYaw = newYaw + ((double) rand() / (RAND_MAX)) * 2 * NOISE_YAW_FACTOR - NOISE_YAW_FACTOR;

		cout << "Robot's Location: " << newX << ", " << newY << ", " << newYaw << endl;

		// Update particles and printing the map
		_slam->update(newX - prevX, newY - prevY, newYaw - prevYaw);

		cout << "----------------------------------------" << endl;
		cout << "BEST PARTICLE: (" << _slam->getXOfBestParticle() << ", " << _slam->getYOfBestParticle() << ", " << _slam->getYawOfBestParticle() << ")" << endl;
		cout << "----------------------------------------" << endl;

		prevX = newX;
		prevY = newY;
		prevYaw = newYaw;

		/////////// End of Particals part ////////

		srcYaw = _Robot->getYaw();
		rotationSide = findRotationSide(srcYaw,dgre);
		_Robot->setSpeed(0,rotationSide);

		while((_Robot->getYaw() < (dgre -1)) || (_Robot->getYaw() > (dgre + 1)))
		{
			_Robot->Read();



		}

		_Robot->setSpeed(0,0);



		//MOVE TO:
		grace = 0.2;

		cout <<  "Starting Moving To:[" << mapDestinationX<< "," << mapDestinationY << "]" <<endl;

		_Robot->setSpeed(0.05,0);


		while(((( _slam->getXOfBestParticle()  ) < (mapDestinationX - grace))||
					   (( _slam->getXOfBestParticle()) > (mapDestinationX + grace))||
					   (( _slam->getYOfBestParticle() ) < (mapDestinationY - grace))||
					   (( _slam->getYOfBestParticle() ) > (mapDestinationY + grace))))

		/*while((((_Robot->getXPos() ) < (mapDestinationX - grace))||
			   ((_Robot->getXPos()) > (mapDestinationX + grace))||
			   ((_Robot->getYPos()) < (mapDestinationY - grace))||
			   ((_Robot->getYPos() ) > (mapDestinationY + grace))))*/
		{

			_Robot->Read();


			/////////// Particals part ////////


			// Get the robot's new location
			newX = _Robot->getXPos();
			newY = _Robot->getYPos();
			newYaw = _Robot->getYaw();

			// Use some noise to simulate real world wrong reads.
			newX = newX + ((double) rand() / (RAND_MAX)) * 2 * NOISE_Location_FACTOR - NOISE_Location_FACTOR;
			newY = newY + ((double) rand() / (RAND_MAX)) * 2 * NOISE_Location_FACTOR - NOISE_Location_FACTOR;
			//newYaw = newYaw + ((double) rand() / (RAND_MAX)) * 2 * NOISE_YAW_FACTOR - NOISE_YAW_FACTOR;

			cout << "Robot's Location: " << newX << ", " << newY << ", " << newYaw << endl;

			// Update particles and printing the map
			_slam->update(newX - prevX, newY - prevY, newYaw - prevYaw);


			prevX = newX;
			prevY = newY;
			prevYaw = newYaw;

			/////////// End of Particals part ////////
		}

		_Robot->setSpeed(0,0.0);

		mapSourceX = _Robot->getXPos();
		mapSourceY = _Robot->getYPos();
		 mapDestinationX = _nextWaypoint->nextWaypoint->getX();
		 mapDestinationY = _nextWaypoint->nextWaypoint->getY();

		_nextWaypoint = _nextWaypoint->nextWaypoint;
	}

}

Manager::~Manager() {
}

