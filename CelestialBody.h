#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include "Position.h"
#include "Vector3D.h"
#include <string>


class CelestialBody
{
private:
    std::string name;
    double radius; //radius of body in KM
    Vector3D position;
    Vector3D velocity;
    Vector3D acceleration;
    double mass;
 

public:
    CelestialBody(std::string name, double positionx, double positiony, double positionz, double mass, double radius, double vectorx, double vectory, double vectorz, double vectorMagnitude);
    void addGravityAcceleration(CelestialBody body2);
    void applyForceAndAccel();
};

#endif
