#include "pch.h"
#include "LandMapCnstructor.h"

void LandMapConstructor::constructLandMad(int water)
{
	percentOfWater = water;
	Eastside.set_percentOfWater(percentOfWater);
	Westside.set_percentOfWater(percentOfWater);
	Eastside.construct();
	Eastside.frameConstructor(1);
	Westside.construct();
	Westside.frameConstructor(1);
}

LandMapConstructor::LandMapConstructor():landSize(1023), landName("noname"), percentOfWater(49)
{
	Eastside.reSetTerrane(landSize, "eastside");
	Westside.reSetTerrane(landSize, "westside");
}

LandMapConstructor::LandMapConstructor(string name, int size, int water)
{
	landSize = size / 2;
	landName = name;
	Eastside.reSetTerrane(landSize, "eastside");
	Westside.reSetTerrane(landSize, "westside");
	this->constructLandMad(water);
}
