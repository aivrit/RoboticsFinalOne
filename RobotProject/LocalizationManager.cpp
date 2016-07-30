#include "LocalizationManager.h"

void LocalizationManager::initFirstParticle(Map* map, double x, double y, double yaw)
{
	_bestParticle = new Particle(x,y,yaw,1,new Map(map));
	addParticle(_bestParticle);
}

void LocalizationManager::update(double deltaX, double deltaY, double deltaYaw)
{
	double bestBelief = 0;
	Particle* bestParticle;

	int toCreate[_numOfParticles];
	int toDelete[_numOfParticles];
	int toCreateCount = 0, toDeleteCount = 0;
	int IndexBestParti;

	// Update the particles according to the robot's scans
	for (int i = 0; i < _numOfParticles; i++)
	{
		_particles[i]->update(deltaX, deltaY, deltaYaw, _robot);


		double currBelief = _particles[i]->getBelief();

		// Delete the particle if it's belief is too low
		if (currBelief < BELIEF_MIN_THRESHOLD)
		{
			toDelete[toDeleteCount] = i;
			toDeleteCount++;
		}
		else
		{
			// Create new particles if the belief is high
			if ((currBelief > BELIEF_MAX_THRESHOLD))
			{
				toCreate[toCreateCount] = i;
				toCreateCount++;
			}

			// Update the best particle
			if (bestBelief < currBelief)
			{
				bestBelief = currBelief;
				IndexBestParti = i;
				bestParticle = _particles[i];
			}
		}
	}



	for (int i = 0; i < toDeleteCount; i++)
	{
		deleteParticle(toDelete[i]);
	}

	for (int i = 0; i < toCreateCount; i++)
	{
		for	(int j = 1; j <= 3; j++)
		{
			if (_numOfParticles < MAX_PARTICLES_NUM)
			{
				Particle* parti = _particles[toCreate[i]]->createNewParticle();
				if (parti != NULL)
				{
					addParticle(parti);
				}
			}
		}
	}

	cout << "Print position In array bestPartical: " << IndexBestParti << endl;
	// Save the best particle
	_bestParticle = bestParticle;
}

bool LocalizationManager::addParticle(Particle* particle)
{
	if (_numOfParticles < MAX_PARTICLES_NUM)
	{
		cout << "Add Partical:( " << particle->getX() << "," <<particle->getY() << ")" << endl;
		_particles[_numOfParticles] = particle;
		_numOfParticles++;
		return true;
	}

	return false;
}

bool LocalizationManager::deleteParticle(int index)
{
	if (_numOfParticles > 0)
	{
		if (_particles[index] == _bestParticle)
		{
			cout << "hey" << endl;
		}

		_particles[index] = _particles[_numOfParticles - 1];
		_particles[_numOfParticles - 1] = NULL;
		_numOfParticles--;
		return true;
	}

	return false;
}

double LocalizationManager::getXOfBestParticle()
{
	return _bestParticle->getX();
}

double LocalizationManager::getYOfBestParticle()
{
	return _bestParticle->getY();
}

double LocalizationManager::getYawOfBestParticle()
{
	return _bestParticle->getYaw();
}

Map* LocalizationManager::getMapBestParticle()
{
	return _bestParticle->getMap();
}

void LocalizationManager::setRobot(Robot* r)
{
	_robot = r;
}

LocalizationManager::~LocalizationManager() {
	delete[] _particles;
}
