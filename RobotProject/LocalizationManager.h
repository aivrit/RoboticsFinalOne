#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_

#define BELIEF_MIN_THRESHOLD 0.25
#define BELIEF_MAX_THRESHOLD 0.8
#define MAX_PARTICLES_NUM 40

#include "Particle.h"
#include "Robot.h"
#include "Map/Map.h"
#include "Consts.h"

using namespace std;

class LocalizationManager {
private:
	Particle* _particles[MAX_PARTICLES_NUM];
	int _numOfParticles;
	Robot* _robot;
	bool addParticle(Particle* par);
	bool deleteParticle(int index);
	int _mapHeight, _mapWidth;
	float _mapResolution;
	Particle* _bestParticle;
public:
	LocalizationManager(Robot* robot, int height, int width, float resolution): _robot(robot), _mapHeight(height),
																		_mapWidth(width), _mapResolution(resolution),
																		_numOfParticles(0){}
	virtual ~LocalizationManager();
	void update(double deltaX, double deltaY, double deltaYaw);
	double getXOfBestParticle();
	double getYOfBestParticle();
	double getYawOfBestParticle();
	Map* getMapBestParticle();
	void initFirstParticle(Map* map, double x, double y, double yaw);
	void setRobot(Robot* r);
};

#endif /* LOCALIZATIONMANAGER_H_ */
