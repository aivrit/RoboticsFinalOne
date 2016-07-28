/*
 * LocalizationManager.cpp
 *
 *  Created on: Jun 17, 2016
 *      Author: colman
 */

#include "LocalizationManager.h"
#include <stdlib.h>
#include <math.h>

LocalizationManager::LocalizationManager(Robot* robot)
{
	this->_robot = robot;
}


// Deletes a particle from the particle list
list<Particle*>::iterator LocalizationManager::deleteParticle(list<Particle*>::iterator it)
{
	return this->_particles.erase(it);
}

void LocalizationManager::generateParticles(Particle* particle)
{
	Location newLocation;

	for (int i=0; i<NUM_PARTICLES_TO_GENERATE; i++)
	{
		// Computer random particle location based on global variables
		int newDX = (rand() % (PARTICLE_RANDOM_RADIUS + 1)) * pow(-1,rand() % 2 + 1);
		int newDY = (rand() % (PARTICLE_RANDOM_RADIUS + 1)) * pow(-1,rand() % 2 + 1);
		double newDYAw = (rand() % (PARTICLE_RANDOM_YAW * 1000) / 1000.0) * pow(-1,rand() % 2 + 1);

		// Change location of new particle based on random radius, and make sure it is non negative.
		newLocation.x = particle->_location->x + newDX;
		newLocation.x = newLocation.x >=0 ? newLocation.x : 0;

		newLocation.y = particle->_location->y + newDY;
		newLocation.y = newLocation.y >=0 ? newLocation.y : 0;

		newLocation.yaw = particle->_location->yaw + newDYAw;
		newLocation.yaw = newLocation.yaw >=0 ? newLocation.yaw : 0;

		// Create new particle with same belief and new location just computed
		Particle* newParticle = new Particle(&newLocation, particle->_belief);

		// Update new belief according to measurements
		newParticle->update(0,0,0,this->_robot->GetLaserRanges());

		// insert new particle to the end of the particle list
		this->_particles.insert(this->_particles.end(),newParticle);
	}
}
	void LocalizationManager::update(int dx, int dy, double dyaw, double* lp_reads)
	{
		for (list<Particle*>::iterator it = this->_particles.begin(); it!=this->_particles.end(); it++)
		{
			Particle* currParticle = *it;
			currParticle->update(dx,dy,dyaw,lp_reads);
		}
	}

	Particle* LocalizationManager::getTopParticle()
	{
		double currMaxBelief = 0;
		Particle* currMaxParticle;

		// Run on all particles
		for (list<Particle*>::iterator it = this->_particles.begin(); it!=this->_particles.end(); it++)
		{
			Particle* currParticle = *it;

			// Check if current is bigger than max
			if (currParticle->_belief > currMaxBelief)
			{
					currMaxBelief = currParticle->_belief;
					currMaxParticle = currParticle;
			}
		}

		// TODO: verify
		return currMaxParticle;
	}




