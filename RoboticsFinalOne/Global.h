/*
 * Global.h
 *
 *  Created on: Jun 17, 2016
 *      Author: colman
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_


struct Location
{
	int x;
	int y;
	double yaw;

};

const int    PARTICLE_RANDOM_RADIUS = 2;
const int    PARTICLE_RANDOM_YAW = 5;
const double PARTICLE_GENERATE_THRESHOLD = 0.9;
const int    NUM_PARTICLES_TO_GENERATE = 3;
const double PARTICLE_DELETE_THRESHOLD = 0.6;
const double PARTICLE_DEC_DIS_PROB_UNIT = 0.2;
const double PARTICLE_DEC_YAW_PROB_UNIT = 3.14 / 6;
const double MIN_PROB_UNIT = 0.01;
const int    MAX_LASER_RANGE = 240;
const int    MAX_LASER_INDEX = 683;
const int    LASER_DEVIATION_UNIT_PIXELS = 3;


static double laserIndexToAngle(int index)
{
	return index * ((double)MAX_LASER_RANGE / MAX_LASER_INDEX);
}

static int meterToPixel(double meter)
{
	return (meter * 100 / 2.5 - 60);
}


#endif /* GLOBAL_H_ */
