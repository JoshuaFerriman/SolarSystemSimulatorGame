#include "CelestialBody.h"
#include "MathConstants.h"
#include <cmath>

CelestialBody::CelestialBody(std::string name, double positionx, double positiony, double positionz, double mass, double radius, double vectorx, double vectory, double vectorz, double vectorMagnitude)
{
    CelestialBody::name = name;
    CelestialBody::position.setVector(positionx, positiony, positionz, 0);
    CelestialBody::velocity.setVector(vectorx, vectory, vectorz, vectorMagnitude);
    CelestialBody::acceleration.setVector(0, 0, 0, 0);
    CelestialBody::mass = mass;
    CelestialBody::radius = radius;
    
}

/*
* 
* 
*  
* 
* 
* 
* 
* 
*/
void CelestialBody::addGravityAcceleration(CelestialBody body2) 
{  
    Vector3D displacementVector = CelestialBody::position.getDisplacementVector(body2.position);

    double Force = G * (body2.mass/pow(displacementVector.magnitude,2)) ;
    displacementVector.setVector(Force * (displacementVector.x/displacementVector.magnitude), Force * (displacementVector.y/displacementVector.magnitude), Force * (displacementVector.z/displacementVector.magnitude));

    CelestialBody::acceleration.addVector(displacementVector);
}

void CelestialBody::applyForceAndAccel()
{

}
  