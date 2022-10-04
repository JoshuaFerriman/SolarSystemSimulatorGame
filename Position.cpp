#include "Position.h"

Position::Position()
{
	Position::x = 0.0f;
	Position::y = 0.0f;
	Position::z = 0.0f;
}

Position::Position(double x, double y, double z)
{
	Position::x = x;
	Position::y = y;
	Position::z = z;
}

void Position::updatePosition(double x, double y, double z)
{
	Position::x = x;
	Position::y = y;
	Position::z = z;
}