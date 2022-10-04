#ifndef CLASS_SOLARSYSTEM_H
#define CLASS_SOLARSYSTEM_H

#include "CelestialBody.h"
#include "AsteroidBelt.h"
#include <vector>

class SolarSystem
{
public:
	std::vector<CelestialBody> bodies;
	std::vector<AsteroidBelt> asteroidBelts;

	SolarSystem();

	void addBody(CelestialBody body);
	void removeBody();
	void updateAll();
};

#endif