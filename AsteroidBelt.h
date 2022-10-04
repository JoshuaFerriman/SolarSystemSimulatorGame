#ifndef ASTEROID_BELT_CLASS_H
#define ASTEROID_BELT_CLASS_H

#include"CelestialBody.h"


class AsteroidBelt
{
public:
	AsteroidBelt(CelestialBody& CelestialBody);
	~AsteroidBelt();

private:
	CelestialBody& parentBody;
	float innerRadius;
	float outerRadius;
	
};

#endif //!ASTEROID_BELT_CLASS_H