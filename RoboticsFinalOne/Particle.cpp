/*
 * Particle.cpp
 *
 *  Created on: Jun 22, 2016
 *      Author: colman
 */


#include "Particle.h"
#include "Global.h"

	Particle::Particle(Location* location, double belief)
	{
		this->_location = new Location();
		this->_location->x = location->x;
		this->_location->y = location->y;
		this->_location->yaw = location->yaw;
		this->_belief = belief;

	}

	double Particle::probByMeasure(double* lp_readings)
	{
		return 1;
	}

	void Particle::update(int dx, int dy, double dyaw, double* lp_readings)
	{

	}

	double Particle::probByMove(int dx, int dy, double dyaw)
	{
		double result = 1;

		if(PARTICLE_DEC_DIS_PROB_UNIT < dx)
		{
			result -= MIN_PROB_UNIT * (int)(dx / PARTICLE_DEC_DIS_PROB_UNIT);
		}

		return result;
	}




