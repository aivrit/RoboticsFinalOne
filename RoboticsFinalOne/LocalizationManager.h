/*
 * LocalizationManager.h
 *
 *  Created on: Jun 17, 2016
 *      Author: colman
 */

#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_

#include "Global.h"
#include <list>
#include "Particle.h"
#include "Robot.h"

using namespace std;

class LocalizationManager
{

	//Data Members
	list<Particle*> _particles;
	Robot* 	        _robot;

	//Methods
	LocalizationManager(Robot* robot);

	void update(int dx, int dy, double dyaw, double* lp_reads);
	void generateParticles(Particle* particle);
	list<Particle*>::iterator deleteParticle(list<Particle*>::iterator it);

};



#endif /* LOCALIZATIONMANAGER_H_ */
