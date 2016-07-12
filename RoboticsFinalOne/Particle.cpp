/*
 * Particle.cpp
 *
 *  Created on: Jun 22, 2016
 *      Author: colman
 */


#include "Particle.h"
#include "Global.h"
#include <math.h>

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
		bool   isObsHit = false;
		double currYaw = DTOR(this->_location->yaw);
		int map[300][300];
		int pixelDeviation = 0;

		// run on all laser indices with a jump of 5 steps
		for (int i = 0; i <= MAX_LASER_INDEX; i += 5)
		{
			double laserAngle = laserIndexToAngle(i);
			double mapDistance = meterToPixel(lp_readings[i]);
			isObsHit = false;

			// for every pixel on the line connecting the robot to the obstacle seen on the current index
			for (int j=0; j<mapDistance + 5 * LASER_DEVIATION_UNIT_PIXELS; j++)
			{
				// get coordinates
				int currXloc= this->_location->x +  (j * cos(currYaw + laserAngle));
				int currYloc = this->_location->y +  (j * sin(currYaw + laserAngle));

				// TODO:
				// if out of bounds, do nothing (might be because of laser deviation add)
				if (currXloc > 300|| currYloc > 300) {

				}

				// if occupied cell, check for deviation and set obstacle hit
				else if (map[currYloc][currXloc] == 1) {
					isObsHit = true;

					double dist = sqrt(pow(currYloc -this->_location->y,2) + pow(currXloc - this->_location->x,2));

					int deviation = (mapDistance - dist) / LASER_DEVIATION_UNIT_PIXELS;
					if (deviation > 0)
					{
						pixelDeviation += deviation;
					}
					else
					{
						pixelDeviation -= deviation;
					}

					break;
				}
			}

			// if obstacle not hit
			if (!isObsHit) {
				pixelDeviation += 10;
			}
		}

		return (1 - pixelDeviation * MIN_PROB_UNIT);
	}

	void Particle::update(int dx, int dy, double dyaw, double* lp_readings)
	{

	}

	double Particle::probByMove(int dx, int dy, double dyaw)
	{
		double result = 1;

		// Return probability for the particle after move of dx
		if(PARTICLE_DEC_DIS_PROB_UNIT < dx)
		{
			result -= MIN_PROB_UNIT * (int)(dx / PARTICLE_DEC_DIS_PROB_UNIT);
		}

		// Return probability for the particle after move of dy
		if(PARTICLE_DEC_DIS_PROB_UNIT < dy)
		{
			result -= MIN_PROB_UNIT * (int)(dy / PARTICLE_DEC_DIS_PROB_UNIT);
		}

		// Return probability for the particle after move of dyaw
		if(PARTICLE_DEC_YAW_PROB_UNIT < dyaw)
		{
			result -= MIN_PROB_UNIT * (int)(dyaw / PARTICLE_DEC_YAW_PROB_UNIT);
		}

		return result;
	}




