#include "ConfigurationManager.h"
#include <fstream>
#include <sstream>

using namespace std;

const char* ConfigurationManager::getMapPath()
{
	return getStrings(MAP_PATH_KEY, 1)[0];
}
double ConfigurationManager::getMapResolutionCM()
{
	return getDoubles(MAP_RESOULTION_CM_KEY, 1)[0];
}
double ConfigurationManager::getGridResolutionCM()
{
	return getDoubles(GRID_RESOULTION_CM_KEY, 1)[0];
}
double* ConfigurationManager::getRobotSize()
{
	return getDoubles(ROBOT_SIZE_KEY, 2);
}
double* ConfigurationManager::getGoal()
{
	return getDoubles(GOAL_KEY, 2);
}
double* ConfigurationManager::getStartLocation()
{
	return getDoubles(START_LOCATION_KEY, 3);
}

double* ConfigurationManager::getDoubles(char* keyName, int countOfDouble)
{
	ifstream inputFile(config_path);
	string line;

	while (getline(inputFile, line))
	{
		istringstream ss(line);
		string name;
		ss >> name;
		const char* key = name.c_str();

		if (strcmp(key, keyName) == 0)
		{
			double* doubles = new double[countOfDouble];
			for (int i = 0; i < countOfDouble; i++)
			{
				ss >> doubles[i];
			}

			return doubles;
		}
	}

	return NULL;
}
char** ConfigurationManager::getStrings(char* keyName, int countOfStrings)
{
	ifstream inputFile(config_path);
	string line;

	while (getline(inputFile, line))
	{
		istringstream ss(line);
		string name;
		ss >> name;
		const char* key = name.c_str();

		if (strcmp(key, keyName) == 0)
		{
			string* strings = new string[countOfStrings];
			for (int i = 0; i < countOfStrings; i++)
			{
				ss >> strings[i];
			}

			char** stringsToReturn = new char*[countOfStrings];
			for (int i = 0; i < countOfStrings; i++)
			{
				stringsToReturn[i] = (char*)strings[i].c_str();
			}
			return stringsToReturn;
		}
	}

	return NULL;
}
