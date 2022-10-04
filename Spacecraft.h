#ifndef SPACECRAFT_CLASS_H
#define SPACECRAFT_CLASS_H

class Spacecraft
{
	enum controlType
	{
		USER,
		NPC
	};

private:
	controlType controlType;
};

#endif //!SPACECRAFT_CLASS_H