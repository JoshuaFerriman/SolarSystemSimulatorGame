#ifndef GAME_MAP_CLASS_H
#define GAME_MAP_CLASS_H

#include "SolarSystem.h"
#include "SpaceCraft.h"


class GameMap
{
	SolarSystem solarSystem;
	std::vector<Spacecraft> spacecrafts;
};

#endif // !GAME_MAP_CLASS_H
