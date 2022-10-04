#include "SolarSystem.h"

SolarSystem::SolarSystem()
{

}

void SolarSystem::addBody(CelestialBody body)
{
	SolarSystem::bodies.push_back(body);
}

void SolarSystem::removeBody()
{
	SolarSystem::bodies.pop_back();
}

void SolarSystem::updateAll()
{
	for (CelestialBody body1 : bodies)
	{
		for (CelestialBody body2 : bodies)
		{
			body1.addGravityAcceleration(body2);

		}
		body1.applyForceAndAccel();
	}
}