//Created by Alexandr Pluzhinskyi 2020//
///////////////////////////////////////


#pragma once
#include <chrono>
using namespace std::chrono;
class LightRand
{
public:
	LightRand();
	LightRand(int min, int max, int seed);
	~LightRand();
	int getVolume();
	int getRandVolume();
	void changeLimits(int min, int max);
	void changeSeed();
protected:
	int checker;
	int prevVol1;
	int prevVol2;
	int prevVol3;
	int volume;
	int limMin;
	int limMax;
	int rand;
	int modulator;
	int correlator;
};

