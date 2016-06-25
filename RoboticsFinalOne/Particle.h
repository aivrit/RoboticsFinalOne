/*
 * Particle.h
 *
 *  Created on: Jun 17, 2016
 *      Author: colman
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Global.h"

class Particle
{

	//Data Members
public:
	double 		 _belief;
	Location*     _location;

	//Methods
	Particle(Location* location, double belief);

	void update(int dx, int dy, double dyaw, double* lp_readings);
	double probByMeasure(double* lp_readings);
	double probByMove(int dx, int dy, double dyaw);

};



#endif /* PARTICLE_H_ */
