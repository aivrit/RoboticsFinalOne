#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_
#include "Consts.h"
#include <string.h>

using namespace std;

class ConfigurationManager {
private:
	char* config_path;
	double* getDoubles(char* key, int countOfDouble);
	char** getStrings(char* key, int countOfStrings);
public:
	ConfigurationManager(char* config_path): config_path(config_path) {}
	const char* getMapPath();
	double getMapResolutionCM();
	double getGridResolutionCM();
	double* getRobotSize();
	double* getGoal();
	double* getStartLocation();
};

#endif
