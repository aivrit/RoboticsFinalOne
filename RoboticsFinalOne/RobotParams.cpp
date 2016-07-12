/*
 * RobotParams.cpp
 *
 *  Created on: Jul 12, 2016
 *      Author: colman
 */

#include "RobotParams.h"
#include "Global.h"
#include <string.h>
#include <fstream>
#include <iostream>

using namespace std;

// Const value
const char* ROBOT_PARAM_FILE = "/home/colman/Desktop/RoboticProject/parameters.txt";

// Global static pointer used to ensure a single instance of the class.
RobotParams* RobotParams::pInstance = NULL;

RobotParams* RobotParams::Instance(){
	if(!pInstance){
		pInstance = new RobotParams(ROBOT_PARAM_FILE);
	}

	return pInstance;
}

RobotParams::RobotParams(const char* robotParamsFilePath){
	char attributeName[200];
	char fileData[10][100];
	fstream inputFile;
	int fileIndex = 0;

	// opening file
	try{
		inputFile.open(robotParamsFilePath, ios::in);
	}
	catch(...){
		cout << "Error opening file." << endl;
	}

	// reading file to stream
	while (!inputFile.eof()){
		inputFile.getline(attributeName, 100, ' ');
		inputFile.getline(fileData[fileIndex], 100, '\n');
		fileIndex++;
	}

	try{
		inputFile.close();
	}
	catch(...){};

	// map file path
	string mapFile = fileData[0];
	if (!mapFile.empty() && mapFile[mapFile.size() - 1] == '\r'){
		mapFile.erase(mapFile.size() - 1);
	}
	this->mapFilePath = new char[100];
	strcpy(this->mapFilePath, mapFile.c_str());

	//  robot start location
	string startLoc = fileData[1];
	this->start.xStartLoc = atoi(startLoc.substr(0, startLoc.find_first_of(' ')).c_str());
	startLoc = startLoc.substr(startLoc.find_first_of(' ') + 1);
	this->start.yStartLoc = atoi(startLoc.substr(0, startLoc.find_first_of(' ')).c_str());
	startLoc = startLoc.substr(startLoc.find_first_of(' ') + 1);
	this->start.yawStartLoc = atoi(startLoc.c_str());

	// robot destination
	string goal= fileData[2];
	this->goal.xDest = atoi(goal.substr(0, goal.find_first_of(' ')).c_str());
	goal = goal.substr(goal.find_first_of(' ') + 1);
	this->goal.yDest = atoi(goal.c_str());

	// robot size
	string robotSize = fileData[3];
	this->robotLength = atoi(robotSize.substr(0, robotSize.find_first_of(' ')).c_str());
	robotSize = robotSize.substr(robotSize.find_first_of(' ') + 1);
	this->robotWidth = atoi(robotSize.c_str());

	// map resolution
	string mapRes = fileData[4];
	this->mapResolutionCM = atof(mapRes.c_str());

	// grid resolution
	string gridRes = fileData[5];
	this->GridResolutionCM = atof(gridRes.c_str());
}

RobotParams::~RobotParams(){
	delete [] this->mapFilePath;
}


