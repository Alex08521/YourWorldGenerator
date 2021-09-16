#pragma once
#include "newTerrane.h"

class LandMapConstructor
{
public:
	void saveLandMap();
	void loadLandMap(string name);
	void constructLandMad(int water);
	void printLandMap();
	void setNameofLandMap(string name);
	void setSizeOfLandMap(int size);
	void setWater(int water);
	LandMapConstructor();
	LandMapConstructor(string name, int size, int water);
	~LandMapConstructor();
private:
	newTerrane Westside;
	newTerrane Eastside;
	string landName;
	int landSize;
	int percentOfWater;
};

