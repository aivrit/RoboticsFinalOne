/*
 * RobotParams.h
 *
 *  Created on: Jul 12, 2016
 *      Author: colman
 */

#ifndef ROBOTPARAMS_H_
#define ROBOTPARAMS_H_


struct StartLocation{
	int xStartLoc = 0;
	int yStartLoc = 0;
	int yawStartLoc = 0;
};

struct Destination{
	int xDest = 0;
	int yDest = 0;
};

class RobotParams {
public:
	//Singleton method
	static RobotParams* Instance();

private:
	//Constructor overload
	RobotParams(const char* robotParamsFilePath);

	//Destructor overload
	~RobotParams();

	// Data Members
	static RobotParams* pInstance;
 	char* mapFilePath;
	StartLocation start;
	Destination goal;
	int robotLength;
	int robotWidth;
	int mapResolutionCM;
	int GridResolutionCM;

};


#endif /* ROBOTPARAMS_H_ */
