#ifndef CLASS_POSITION_H
#define CLASS_POSITION_H

class Position
{

public:
	double x;
	double y;
	double z;

	Position();
	Position(double x, double y, double z);
	
	void updatePosition(double x, double y, double z);
};

#endif