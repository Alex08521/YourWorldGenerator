#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <fstream>
#include "newTerrane.h"

using namespace std;

newTerrane::newTerrane(short terr,string name):terrSize(terr),name(name)
{
	scope.remakeField(terrSize);
	forest.remakeField(terrSize);
	//civilization.remakeField(terrSize);
	climat_zone.remakeField(terrSize);
	biome.remakeField(terrSize);
	//zone_name.remakeField(terrSize);
	//resourses.remakeField(terrSize);
	percentOfWater = 49;
	numOfContinents = 6;
	this -> construct();
}

newTerrane::newTerrane()
{
	terrSize = 8160;
	name = "noname";
	scope.remakeField(terrSize);
	forest.remakeField(terrSize);
	//civilization.remakeField(terrSize);
	climat_zone.remakeField(terrSize);
	biome.remakeField(terrSize);
	//zone_name.remakeField(terrSize);
	//resourses.remakeField(terrSize);
	numOfContinents = 6;
	percentOfWater = 49;
}

newTerrane::~newTerrane()
{
	scope.~Field2D();
	forest.~Field2D();
	//civilization.~Field2D();
	climat_zone.~Field2D();
	biome.~Field2D();
	//zone_name.~Field2D();
	//resourses.~Field2D();
}
		
void newTerrane::construct()
{
	cout << "Generating landscape" << endl;
	this->clear();
	cout << "#";
	this->climateZoneConstructor();
	cout << "#";
	int numOfCicles;
	if (numOfContinents < 1)
	{
		numOfCicles = 0;
	}
	else
	{
		numOfCicles = ((terrSize - ((terrSize/ 100) * (100 - percentOfWater))) / numOfContinents);
	}
	cout << "#";

	int numOfRivers = (percentOfWater/10);

	cout << "#";

	if (percentOfWater > 99)
	{
		this->zeroDelete(1);
	}
	else
	{
		this->contconstr();
/*
		cout << "Correktion begins:" << endl;

		for (int y = 0; y < terrSize; y++)
		{
			for (int x = 0; x < terrSize; x++)
			{
				scope.moveToPnt(x, y);
				if (scope.get_elem() == lowland)
				{
					this->corrLand();
				}
			}
		}
		cout << "#";
		for (int y = 0; y < terrSize; y++)
		{
			for (int x = 0; x < terrSize; x++)
			{
				scope.moveToPnt(x, y);
				if (scope.get_elem() == midland)
				{
					this->corrLand();
				}
			}
		}
		cout << "#";
		for (int y = 0; y < terrSize; y++)
		{
			for (int x = 0; x < terrSize; x++)
			{
				scope.moveToPnt(x, y);
				if (scope.get_elem() == highland)
				{
					this->corrLand();
				}
			}
		}
		cout << "#";
		for (int y = 0; y < terrSize; y++)
		{
			for (int x = 0; x < terrSize; x++)
			{
				scope.moveToPnt(x, y);
				if (scope.get_elem() == mountain)
				{
					this->corrLand();
				}
			}
		}
		cout << "#" << endl;
		cout << "Correktion complete" << endl;
*/		
		if (percentOfWater > 1)
		{
			this->zeroDelete(1);
			cout << "Ocean complete" << endl;
		}
		else
		{
			this->zeroDelete(2);
			cout << "Wasteland complete" << endl;
		}
		
		for (int y = 0; y < terrSize; y++)
		{
			for (int x = 0; x < terrSize; x++)
			{
				scope.moveToPnt(x, y);
				this->logicCorr(scope.get_elem());
			}
		}
		cout << "Logical correction complete" << endl;

		if (percentOfWater > 15)
		{
			this->riverConstructor(numOfRivers);

			cout << "River complete" << endl;
		}


		for (int y = 0; y < terrSize; y++)
		{
			for (short x = 0; x < terrSize; x++)
			{
				scope.moveToPnt(x, y);
				if (scope.get_elem() == 1) { this->logicCorr(scope.get_elem()); }
			}
		}

		cout << "Beaches complete" << endl;

		for (int y = 0; y < terrSize; y++)
		{
			for (short x = 0; x < terrSize; x++)
			{
				scope.moveToPnt(x, y);
				this->artifactDeleter();
			}
		}

		cout << "Artifacts delete" << endl;
/*
		if (percentOfWater > 1 && percentOfWater < 99)
		{
			this->forest_generate();

			cout << "Forests complete" << endl;
		}
*/
	}

	this->biomeConstructor();

	cout << "Biomes complete" << endl;
	
	cout<<"Landscape comlete"<<endl;
}

void newTerrane::printScope(bool climates, bool biomes)
{
	settings.antialiasingLevel = 0;
	window.create(VideoMode(1600, 900), name, Style::Default, settings);
	while (window.isOpen())
	{
		for (int i=0;i<terrSize;i++)
		{
			for (int j=0;j<terrSize;j++)
			{
				Vertex pixel[1];
				scope.moveToPnt(j, i);
				biome.moveToPnt(j, i);
			
				switch(scope.get_elem())
				{
					case water:
						pixel[0] = Vertex(Vector2f(j, i), Color(1, 1, 1));
						break;
					case lowland:
						pixel[0] = Vertex(Vector2f(j, i), Color(30,30,30));
						break;
					case midland:
						pixel[0] = Vertex(Vector2f(j, i), Color(60,60,60));
						break;
					case highland:
						pixel[0] = Vertex(Vector2f(j, i), Color(150, 150, 150));
						break;
					case cliff:
						pixel[0] = Vertex(Vector2f(j, i), Color(220, 220, 220));
						break;
					case mountain:
						pixel[0] = Vertex(Vector2f(j, i), Color(220, 220, 220));
						break;
				}

				if (biomes == true)
				{
					switch (biome.get_elem())
					{
					case icewater:
						pixel[0] = Vertex(Vector2f(j, i), Color(128, 255, 255));
						break;
					case coldwater:
						pixel[0] = Vertex(Vector2f(j, i), Color(90, 209, 254));
						break;
					case temperatewater:
						pixel[0] = Vertex(Vector2f(j, i), Color(0, 128, 255));
						break;
					case warmwater:
						pixel[0] = Vertex(Vector2f(j, i), Color(0, 108, 217));
						break;
					case coldforest:
						pixel[0] = Vertex(Vector2f(j, i), Color(0, 128, 64));
						break;
					case temperateforest:
						pixel[0] = Vertex(Vector2f(j, i), Color(0, 168, 84));
						break;
					case thundraswamp:
						pixel[0] = Vertex(Vector2f(j, i), Color(116, 186, 186));
						break;
					case swamp:
						pixel[0] = Vertex(Vector2f(j, i), Color(60, 119, 119));
						break;
					case oasis:
						pixel[0] = Vertex(Vector2f(j, i), Color(128, 255, 128));
						break;
					case arcticdesert:
						pixel[0] = Vertex(Vector2f(j, i), Color(255, 255, 255));
						break;
					case thundrawasteland:
						pixel[0] = Vertex(Vector2f(j, i), Color(216, 216, 216));
						break;
					case wasteland:
						pixel[0] = Vertex(Vector2f(j, i), Color(155, 155, 0));
						break;
					case steppe:
						pixel[0] = Vertex(Vector2f(j, i), Color(204, 204, 0));
						break;
					case desert:
						pixel[0] = Vertex(Vector2f(j, i), Color(255, 1198, 140));
						break;
					case thundrafield:
						pixel[0] = Vertex(Vector2f(j, i), Color(179, 255, 217));
						break;
					case valley:
						pixel[0] = Vertex(Vector2f(j, i), Color(0, 149, 74));
						break;
					case warmwalley:
						pixel[0] = Vertex(Vector2f(j, i), Color(0, 187, 94));
						break;
					case vulcan:
						pixel[0] = Vertex(Vector2f(j, i), Color(198, 0, 0));
						break;
					case icepike:
						pixel[0] = Vertex(Vector2f(j, i), Color(233, 233, 233));
						break;
					case magmapike:
						pixel[0] = Vertex(Vector2f(j, i), Color(128, 128, 128));
						break;
					case jungle:
						pixel[0] = Vertex(Vector2f(j, i), Color(0, 232, 0));
						break;
					}
				}
				window.draw(pixel, 1, Points);
			}
		
		}
	window.display();
	
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
			{	// Тогда закрываем его
				window.close();
			}
			if (event.type == Event::Resized)
			{
				window.display();
			}
		}
	}
}

void newTerrane::clear()
{
	for(int i=0;i<1024;i++)
	{
		for(int j=0;j<1024;j++)
		{
			scope.moveToPnt(i,j);
			forest.moveToPnt(i, j);
			biome.moveToPnt(i, j);
			//civilization.moveToPnt(i, j);
			climat_zone.moveToPnt(i, j);
			//zone_name.moveToPnt(i, j);
			//resourses.moveToPnt(i, j);
			scope.set_elem(nowidth);
			forest.set_elem(false);
			biome.set_elem(nobiome);
			//civilization.set_elem(wild);
			climat_zone.set_elem(noclimate);
			//zone_name.set_elem(L"Nonamed zone");
			//resourses.set_elem(нетресурсов);
		}
	}
	window.clear(Color::Black);
}

string newTerrane::getName()
{
	return(name);
}

bool newTerrane::constrLand(int X, int Y, int sizeOfContSideX, int sizeOfContSideY, short filler, const char worktype[])
{
	int edgeX = X + sizeOfContSideX;
	int edgeY = Y + sizeOfContSideY;
	int downY = edgeY;
	if (filler == 0)
	{
		for (int y = Y; y < edgeY; y++)
		{
			for (int x = X; x < edgeX; x++)
			{
				scope.moveToPnt(x, y);
				int solid = scope.get_elem();
				if (solid != filler)
				{
					if (scope.move_up() == true)
					{
						scope.set_elem(this->typeOfLandVariator(solid, scope.get_elem(), worktype));
						scope.moveToPnt(x, y);
					}
					if (scope.move_upl() == true)
					{
						scope.set_elem(this->typeOfLandVariator(solid, scope.get_elem(), worktype));
						scope.moveToPnt(x, y);
					}
					if (scope.move_upr() == true)
					{
						scope.set_elem(this->typeOfLandVariator(solid, scope.get_elem(), worktype));
						scope.moveToPnt(x, y);
					}
					if (scope.move_down() == true)
					{
						scope.set_elem(this->typeOfLandVariator(solid, scope.get_elem(), worktype));
						scope.moveToPnt(x, y);
					}
					if (scope.move_downr() == true)
					{
						scope.set_elem(this->typeOfLandVariator(solid, scope.get_elem(), worktype));
						scope.moveToPnt(x, y);
					}
					if (scope.move_downl() == true)
					{
						scope.set_elem(this->typeOfLandVariator(solid, scope.get_elem(), worktype));
						scope.moveToPnt(x, y);
					}
					if (scope.move_right() == true)
					{
						scope.set_elem(solid - 1);
						scope.moveToPnt(x, y);
					}
					if (scope.move_left() == true)
					{
						scope.set_elem(this->typeOfLandVariator(solid, scope.get_elem(), worktype));
						scope.moveToPnt(x, y);
					}
				}

				downY = downY - y;

				scope.moveToPnt(x, downY);
				solid = scope.get_elem();
				if (scope.get_elem() != filler)
				{
					if (scope.move_up() == true)
					{
						scope.set_elem(this->typeOfLandVariator(solid, scope.get_elem(), worktype));
						scope.moveToPnt(x, downY);
					}
					if (scope.move_upl() == true)
					{
						scope.set_elem(this->typeOfLandVariator(solid, scope.get_elem(), worktype));
						scope.moveToPnt(x, downY);
					}
					if (scope.move_upr() == true)
					{
						scope.set_elem(this->typeOfLandVariator(solid, scope.get_elem(), worktype));
						scope.moveToPnt(x, downY);
					}
					if (scope.move_down() == true)
					{
						scope.set_elem(this->typeOfLandVariator(solid, scope.get_elem(), worktype));
						scope.moveToPnt(x, downY);
					}
					if (scope.move_downr() == true)
					{
						scope.set_elem(this->typeOfLandVariator(solid, scope.get_elem(), worktype));
						scope.moveToPnt(x, downY);
					}
					if (scope.move_downl() == true)
					{
						scope.set_elem(this->typeOfLandVariator(solid, scope.get_elem(), worktype));
						scope.moveToPnt(x, downY);
					}
					if (scope.move_right() == true)
					{
						scope.set_elem(solid - 1);
						scope.moveToPnt(x, downY);
					}
					if (scope.move_left() == true)
					{
						scope.set_elem(this->typeOfLandVariator(solid, scope.get_elem(), worktype));
						scope.moveToPnt(x, downY);
					}
				}
			}
		}
	}
	else
	{
		for (int y = Y; y < edgeY; y++)
		{
			for (int x = X; x < edgeX; x++)
			{
				scope.moveToPnt(x, y);
				if (scope.get_elem() == filler)
				{
					if (scope.move_up() == true)
					{
						scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler, worktype));
						scope.moveToPnt(x, y);
					}
					if (scope.move_upl() == true)
					{
						scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler, worktype));
						scope.moveToPnt(x, y);
					}
					if (scope.move_upr() == true)
					{
						scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler, worktype));
						scope.moveToPnt(x, y);
					}
					if (scope.move_down() == true)
					{
						scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler, worktype));
						scope.moveToPnt(x, y);
					}
					if (scope.move_downr() == true)
					{
						scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler, worktype));
						scope.moveToPnt(x, y);
					}
					if (scope.move_downl() == true)
					{
						scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler, worktype));
						scope.moveToPnt(x, y);
					}
					if (scope.move_right() == true)
					{
						scope.set_elem(filler - 1);
						scope.moveToPnt(x, y);
					}
					if (scope.move_left() == true)
					{
						scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler, worktype));
						scope.moveToPnt(x, y);
					}
				}

				downY = downY - y;

				scope.moveToPnt(x, downY);
				if (scope.get_elem() == filler)
				{
					if (scope.move_up() == true)
					{
						scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler, worktype));
						scope.moveToPnt(x, downY);
					}
					if (scope.move_upl() == true)
					{
						scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler, worktype));
						scope.moveToPnt(x, downY);
					}
					if (scope.move_upr() == true)
					{
						scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler, worktype));
						scope.moveToPnt(x, downY);
					}
					if (scope.move_down() == true)
					{
						scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler, worktype));
						scope.moveToPnt(x, downY);
					}
					if (scope.move_downr() == true)
					{
						scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler, worktype));
						scope.moveToPnt(x, downY);
					}
					if (scope.move_downl() == true)
					{
						scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler, worktype));
						scope.moveToPnt(x, downY);
					}
					if (scope.move_right() == true)
					{
						scope.set_elem(filler - 1);
						scope.moveToPnt(x, downY);
					}
					if (scope.move_left() == true)
					{
						scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler, worktype));
						scope.moveToPnt(x, downY);
					}
				}
			}
		}
	}

	return true;
}

bool newTerrane::logicCorr(short a)
{
	if (a == 0)
	{
		return false;
	}
	int nowX = scope.get_nowx();
	int nowY = scope.get_nowy();
	for (int u = 1; u < 9; u++)
	{
		scope.moveToPnt(nowX, nowY);
		switch (u)
		{
		case 1:
			if (scope.move_downr() == true)
			{
				scope.set_elem(this->typeOfLandRelocator(scope.get_elem(), a));
			}
			break;
		case 2:
			if (scope.move_downl() == true)
			{
				scope.set_elem(this->typeOfLandRelocator(scope.get_elem(), a));
			}
			break;
		case 3:
			if (scope.move_upr() == true)
			{
				scope.set_elem(this->typeOfLandRelocator(scope.get_elem(), a));
			}
			break;
		case 4:
			if (scope.move_upl() == true)
			{
				scope.set_elem(this->typeOfLandRelocator(scope.get_elem(), a));
			}
			break;
		case 5:
			if (scope.move_down() == true)
			{
				scope.set_elem(this->typeOfLandRelocator(scope.get_elem(), a));
			}
			break;
		case 6:
			if (scope.move_up() == true)
			{
				scope.set_elem(this->typeOfLandRelocator(scope.get_elem(), a));
			}
			break;
		case 7:
			if (scope.move_right() == true)
			{
				scope.set_elem(this->typeOfLandRelocator(scope.get_elem(), a));
			}
			break;
		case 8:
			if (scope.move_left() == true)
			{
				scope.set_elem(this->typeOfLandRelocator(scope.get_elem(), a));
			}
			break;
		}
		scope.moveToPnt(nowX, nowY);
	}
	scope.moveToPnt(nowX, nowY);
	return true;
}

/*void newTerrane::spiralGen(short sizeofSide, int localX, int localY, uint8_t filler)
{
	int right = 1;
	int up = 2;
	int left = 2;
	int down = 2;
	int red = sizeofSide / 2;
	scope.moveToPnt(localX, localY);
	for (int i = 0; i < red; i++)
	{
		scope.move_right();
		if (scope.get_elem() == filler)
		{
			if (scope.move_up() == true)
			{
				scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
			}
			if (scope.move_upl() == true)
			{
				scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
			}
			if (scope.move_upr() == true)
			{
				scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
			}
			if (scope.move_down() == true)
			{
				scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
			}
			if (scope.move_downr() == true)
			{
				scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
			}
			if (scope.move_downl() == true)
			{
				scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
			}
			if (scope.move_right() == true)
			{
				scope.set_elem(filler - 1);
			}
			if (scope.move_left() == true)
			{
				scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
			}

			for (int jk = 0; jk < right; jk++)
			{
				scope.move_up();
				if (scope.move_up() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_upl() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_upr() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_down() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_downr() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_downl() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_right() == true)
				{
					scope.set_elem(filler - 1);
				}
				if (scope.move_left() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
			}
			right = right + 2;
			for (int jh = 0; jh < up; jh++)
			{
				scope.move_left();
				if (scope.move_up() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_upl() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_upr() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_down() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_downr() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_downl() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_right() == true)
				{
					scope.set_elem(filler - 1);
				}
				if (scope.move_left() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
			}
			up = up + 2;
			for (int jf = 0; jf < left; jf++)
			{
				scope.move_down();
				if (scope.move_up() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_upl() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_upr() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_down() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_downr() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_downl() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_right() == true)
				{
					scope.set_elem(filler - 1);
				}
				if (scope.move_left() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
			}
			left = left + 2;
			for (int jd = 0; jd < down; jd++)
			{
				scope.move_right();
				if (scope.move_up() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_upl() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_upr() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_down() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_downr() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_downl() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
				if (scope.move_right() == true)
				{
					scope.set_elem(filler - 1);
				}
				if (scope.move_left() == true)
				{
					scope.set_elem(this->typeOfLandVariator(scope.get_elem(), filler));
				}
			}
			down = down + 2;
		}
	}
}*/

void newTerrane::spiralCorrection()
{
	int right = 1;
	int up = 2;
	int left = 2;
	int down = 2;
	int red = (terrSize / 2);
	scope.moveToCoordinate(0, 0);
	int x = scope.get_nowx();
	int y = scope.get_nowy();
	int log = scope.get_elem();
	corrLand();
	if (log != 0) scope.moveToPnt(x, y);
	for (int i = 0; i < red; i++)
	{
		scope.move_right();
		x = scope.get_nowx();
		y = scope.get_nowy();
		log = scope.get_elem();
		corrLand();
		if (log != 0) scope.moveToPnt(x, y);
		for (int jk = 0; jk < right; jk++)
		{
			scope.move_up();
			x = scope.get_nowx();
			y = scope.get_nowy();
			log = scope.get_elem();
			corrLand();
			if (log != 0) scope.moveToPnt(x, y);
		}
		right = right + 2;
		for (int jh = 0; jh < up; jh++)
		{
			scope.move_left();
			x = scope.get_nowx();
			y = scope.get_nowy();
			log = scope.get_elem();
			corrLand();
			if (log != 0) scope.moveToPnt(x, y);
		}
		up = up + 2;
		for (int jf = 0; jf < left; jf++)
		{
			scope.move_down();
			x = scope.get_nowx();
			y = scope.get_nowy();
			log = scope.get_elem();
			corrLand();
			if (log != 0) scope.moveToPnt(x, y);
		}
		left = left + 2;
		for (int jd = 0; jd < down; jd++)
		{
			scope.move_right();
			x = scope.get_nowx();
			y = scope.get_nowy();
			log = scope.get_elem();
			corrLand();
			if (log != 0) scope.moveToPnt(x, y);
		}
		down = down + 2;
	}
}

void newTerrane::spiralLogicCorrection()
{
	int right = 1;
	int up = 2;
	int left = 2;
	int down = 2;
	int red = (terrSize / 2);
	scope.moveToCoordinate(0, 0);
	int x = scope.get_nowx();
	int y = scope.get_nowy();
	int log = scope.get_elem();
	this->logicCorr(scope.get_elem());
	if (log != 0) scope.moveToPnt(x, y);
	for (int i = 0; i < red; i++)
	{
		scope.move_right();
		x = scope.get_nowx();
		y = scope.get_nowy();
		log = scope.get_elem();
		this->logicCorr(scope.get_elem());
		if (log != 0) scope.moveToPnt(x, y);
		for (int jk = 0; jk < right; jk++)
		{
			scope.move_up();
			x = scope.get_nowx();
			y = scope.get_nowy();
			log = scope.get_elem();
			this->logicCorr(scope.get_elem());
			if (log != 0) scope.moveToPnt(x, y);
		}
		right = right + 2;
		for (int jh = 0; jh < up; jh++)
		{
			scope.move_left();
			x = scope.get_nowx();
			y = scope.get_nowy();
			log = scope.get_elem();
			this->logicCorr(scope.get_elem());
			if (log != 0) scope.moveToPnt(x, y);
		}
		up = up + 2;
		for (int jf = 0; jf < left; jf++)
		{
			scope.move_down();
			x = scope.get_nowx();
			y = scope.get_nowy();
			log = scope.get_elem();
			this->logicCorr(scope.get_elem());
			if (log != 0) scope.moveToPnt(x, y);
		}
		left = left + 2;
		for (int jd = 0; jd < down; jd++)
		{
			scope.move_right();
			x = scope.get_nowx();
			y = scope.get_nowy();
			log = scope.get_elem();
			this->logicCorr(scope.get_elem());
			if (log != 0) scope.moveToPnt(x, y);
		}
		down = down + 2;
	}
}

void newTerrane::forest_generate()
{
	cout << "Forest constructing begins:" << endl;
	for (int i = 0; i < terrSize; i++)
	{
		for (int j = 0; j < terrSize; j++)
		{
			scope.moveToPnt(j, i);
			forest.moveToPnt(j, i);
			climat_zone.moveToPnt(j, i);
			if (scope.get_elem() != water && scope.get_elem() != cliff && scope.get_elem() != mountain)
			{

				if (climat_zone.get_elem() == arctic)
				{
					forest.set_elem(false);
				}
				else if (climat_zone.get_elem() == thundra)
				{
					if (this->ScopeScaner(water, terrSize/10, 15, 0) == true)
					{
						forest.set_elem(true);
					}
					else
					{
						forest.set_elem(false);
					}
				}
				else if (climat_zone.get_elem() == temperate)
				{
					if (this->ScopeScaner(water, terrSize/4, 10, 0) == true)
					{
						forest.set_elem(true);
					}
					else
					{
						forest.set_elem(false);
					}
				}
				else if (climat_zone.get_elem() == subtropical)
				{
					if (this->ScopeScaner(water, terrSize/5, 5, 0) == true)
					{
						forest.set_elem(true);
					}
					else
					{
						forest.set_elem(false);
					}
				}
				else if (climat_zone.get_elem() == tropical)
				{
					if (this->ScopeScaner(water, terrSize / 6, 3, 0) == true)
					{
						forest.set_elem(true);
					}
					else
					{
						forest.set_elem(false);
					}
				}
				else if (climat_zone.get_elem() == subequatorial)
				{
					if (this->ScopeScaner(water, terrSize / 8, 1, 0) == true)
					{
						forest.set_elem(true);
					}
					else
					{
						forest.set_elem(false);
					}
				}
				else if (climat_zone.get_elem() == equatorial)
				{
					if (this->ScopeScaner(water, terrSize / 10, 0, 0) == true)
					{
						forest.set_elem(true);
					}
					else
					{
						forest.set_elem(false);
					}
				}
				else
				{
					if (this->ScopeScaner(water, terrSize / 5, 15, 0) == true)
					{
						forest.set_elem(true);
					}
					else
					{
						forest.set_elem(false);
					}
				}
				
			}
			else
			{
				forest.set_elem(false);
			}
		}
		if (i % 100 == 0)
		{
			cout << "#";
		}
	}
	cout << "#" << endl;
}

void newTerrane::showParam()
{
	cout << "Element = " << scope.get_elem() << endl;
	scope.get_coordinate();
	scope.get_nowPos();
}

void newTerrane::history_years_set(short a)
{
	history_yeras = a;
}

bool newTerrane::corrLand()
{
	unsigned short noelem = 0;
	unsigned short waters = 0;
	unsigned short lowlands = 0;
	unsigned short middlelands = 0;
	unsigned short highlands = 0;
	unsigned short rocks = 0;
	unsigned short mounts = 0;
	short needCorrX = scope.get_nowx();
	short needCorrY = scope.get_nowy();
	for (unsigned short u = 1; u < 9; u++)
	{
		scope.moveToPnt(needCorrX, needCorrY);
		switch (u)
		{
		case 1:
			if (scope.move_downr() == true)
			{
				switch (scope.get_elem())
				{
				case mountain:
					mounts++;
					break;
					//case cliff:
					//	rocks++;
					//	break;
				case highland:
					highlands++;
					break;
				case midland:
					middlelands++;
					break;
				case lowland:
					lowlands++;
					break;
					//case water:
					//	waters++;
					//	break;
					//case nowidth:
					//	noelem++;
					//	break;
				}
			}
			break;
		case 2:
			if (scope.move_downl() == true)
			{
				switch (scope.get_elem())
				{
				case mountain:
					mounts++;
					break;
					//case cliff:
					//	rocks++;
					//	break;
				case highland:
					highlands++;
					break;
				case midland:
					middlelands++;
					break;
				case lowland:
					lowlands++;
					break;
					//case water:
					//	waters++;
					//	break;
					//case nowidth:
					//	noelem++;
					//	break;
				}
			}
			break;
		case 3:
			if (scope.move_upr() == true)
			{
				switch (scope.get_elem())
				{
				case mountain:
					mounts++;
					break;
					//case cliff:
					//	rocks++;
					//	break;
				case highland:
					highlands++;
					break;
				case midland:
					middlelands++;
					break;
				case lowland:
					lowlands++;
					break;
					//case water:
					//	waters++;
					//	break;
					//case nowidth:
					//	noelem++;
					//	break;
				}
			}
			break;
		case 4:
			if (scope.move_upl() == true)
			{
				switch (scope.get_elem())
				{
				case mountain:
					mounts++;
					break;
					//case cliff:
					//	rocks++;
					//	break;
				case highland:
					highlands++;
					break;
				case midland:
					middlelands++;
					break;
				case lowland:
					lowlands++;
					break;
					//case water:
					//	waters++;
					//	break;
					//case nowidth:
					//	noelem++;
					//	break;
				}
			}
			break;
		case 5:
			if (scope.move_down() == true)
			{
				switch (scope.get_elem())
				{
				case mountain:
					mounts++;
					break;
					//case cliff:
					//	rocks++;
					//	break;
				case highland:
					highlands++;
					break;
				case midland:
					middlelands++;
					break;
				case lowland:
					lowlands++;
					break;
					//case water:
					//	waters++;
					//	break;
					//case nowidth:
					//	noelem++;
					//	break;
				}
			}
			break;
		case 6:
			if (scope.move_up() == true)
			{
				switch (scope.get_elem())
				{
				case mountain:
					mounts++;
					break;
					//case cliff:
					//	rocks++;
					//	break;
				case highland:
					highlands++;
					break;
				case midland:
					middlelands++;
					break;
				case lowland:
					lowlands++;
					break;
					//case water:
					//	waters++;
					//	break;
					//case nowidth:
					//	noelem++;
					//	break;
				}
			}
			break;
		case 7:
			if (scope.move_right() == true)
			{
				switch (scope.get_elem())
				{
				case mountain:
					mounts++;
					break;
					//case cliff:
					//	rocks++;
					//	break;
				case highland:
					highlands++;
					break;
				case midland:
					middlelands++;
					break;
				case lowland:
					lowlands++;
					break;
					//case water:
					//	waters++;
					//	break;
					//case nowidth:
					//	noelem++;
					//	break;
				}
			}
			break;
		case 8:
			if (scope.move_left() == true)
			{
				switch (scope.get_elem())
				{
				case mountain:
					mounts++;
					break;
				//case cliff:
				//	rocks++;
				//	break;
				case highland:
					highlands++;
					break;
				case midland:
					middlelands++;
					break;
				case lowland:
					lowlands++;
					break;
				//case water:
				//	waters++;
				//	break;
				//case nowidth:
				//	noelem++;
				//	break;
				}
			}
			break;
		}
	}

	scope.moveToPnt(needCorrX, needCorrY);

	//if (noelem > waters && noelem > lowlands && noelem > middlelands && noelem > highlands && noelem > rocks && noelem > mounts);
	//else if (waters > noelem && waters > lowlands && waters > middlelands && waters > highlands && waters > rocks && waters > mounts) 
	//	d8.randomize(100) > 93 ? scope.set_elem(lowland) : scope.set_elem(water);
	if (lowlands > noelem && lowlands > waters && lowlands > middlelands && lowlands > highlands && lowlands > rocks && lowlands > mounts) scope.set_elem(lowland);
	else if (middlelands > noelem && middlelands > waters && middlelands > lowlands && middlelands > highlands && middlelands > rocks && middlelands > mounts) scope.set_elem(midland);
	else if (highlands > noelem && highlands > waters && highlands > middlelands && highlands > lowlands && highlands > rocks && highlands > mounts) scope.set_elem(highland);
	//else if (rocks > noelem && rocks > waters && rocks > middlelands && rocks > highlands && rocks > lowlands && rocks > mounts) scope.set_elem(5);
	else if (mounts > noelem && mounts > waters && mounts > middlelands && mounts > highlands && mounts > rocks && mounts > lowlands) scope.set_elem(mountain);
	else 
	{
		//d8.randomize(100) > 90 ? scope.set_elem(mountain) : d8.randomize(100) > 70 ? scope.set_elem(highland) : d8.randomize(100) > 50 ? scope.set_elem(midland) : 
		//	d8.randomize(100) > 30 ? scope.set_elem(lowland) : scope.set_elem(nowidth);
		return false;
	}
	return true;
}

bool newTerrane::artifactDeleter()
{
	unsigned short noelem = 0;
	unsigned short waters = 0;
	unsigned short lowlands = 0;
	unsigned short middlelands = 0;
	unsigned short highlands = 0;
	unsigned short rocks = 0;
	unsigned short mounts = 0;
	unsigned short nomove = 0;
	short needCorrX = scope.get_nowx();
	short needCorrY = scope.get_nowy();
	for (unsigned short u = 1; u < 9; u++)
	{
		scope.moveToPnt(needCorrX, needCorrY);
		switch (u)
		{
		case 1:
			if (scope.move_downr() == true)
			{
				switch (scope.get_elem())
				{
				case 6:
					mounts++;
					break;
				case 5:
					rocks++;
					break;
				case 4:
					highlands++;
					break;
				case 3:
					middlelands++;
					break;
				case 2:
					lowlands++;
					break;
				case 1:
					waters++;
					break;
				case 0:
					noelem++;
					break;
				}
			}
			else
			{
				nomove++;
			}
		case 2:
			if (scope.move_downl() == true)
			{
				switch (scope.get_elem())
				{
				case 6:
					mounts++;
					break;
				case 5:
					rocks++;
					break;
				case 4:
					highlands++;
					break;
				case 3:
					middlelands++;
					break;
				case 2:
					lowlands++;
					break;
				case 1:
					waters++;
					break;
				case 0:
					noelem++;
					break;
				}
			}
			else
			{
				nomove++;
			}
			break;
		case 3:
			if (scope.move_upr() == true)
			{
				switch (scope.get_elem())
				{
				case 6:
					mounts++;
					break;
				case 5:
					rocks++;
					break;
				case 4:
					highlands++;
					break;
				case 3:
					middlelands++;
					break;
				case 2:
					lowlands++;
					break;
				case 1:
					waters++;
					break;
				case 0:
					noelem++;
					break;
				}
			}
			else
			{
				nomove++;
			}
			break;
		case 4:
			if (scope.move_upl() == true)
			{
				switch (scope.get_elem())
				{
				case 6:
					mounts++;
					break;
				case 5:
					rocks++;
					break;
				case 4:
					highlands++;
					break;
				case 3:
					middlelands++;
					break;
				case 2:
					lowlands++;
					break;
				case 1:
					waters++;
					break;
				case 0:
					noelem++;
					break;
				}
			}
			else
			{
				nomove++;
			}
			break;
		case 5:
			if (scope.move_up() == true)
			{
				switch (scope.get_elem())
				{
				case 6:
					mounts++;
					break;
				case 5:
					rocks++;
					break;
				case 4:
					highlands++;
					break;
				case 3:
					middlelands++;
					break;
				case 2:
					lowlands++;
					break;
				case 1:
					waters++;
					break;
				case 0:
					noelem++;
					break;
				}
			}
			else
			{
				nomove++;
			}
			break;
		case 6:
			if (scope.move_down() == true)
			{
				switch (scope.get_elem())
				{
				case 6:
					mounts++;
					break;
				case 5:
					rocks++;
					break;
				case 4:
					highlands++;
					break;
				case 3:
					middlelands++;
					break;
				case 2:
					lowlands++;
					break;
				case 1:
					waters++;
					break;
				case 0:
					noelem++;
					break;
				}
			}
			else
			{
				nomove++;
			}
			break;
		case 7:
			if (scope.move_right() == true)
			{
				switch (scope.get_elem())
				{
				case 6:
					mounts++;
					break;
				case 5:
					rocks++;
					break;
				case 4:
					highlands++;
					break;
				case 3:
					middlelands++;
					break;
				case 2:
					lowlands++;
					break;
				case 1:
					waters++;
					break;
				case 0:
					noelem++;
					break;
				}
			}
			else
			{
				nomove++;
			}
			break;
		case 8:
			if (scope.move_left() == true)
			{
				switch (scope.get_elem())
				{
				case 6:
					mounts++;
					break;
				case 5:
					rocks++;
					break;
				case 4:
					highlands++;
					break;
				case 3:
					middlelands++;
					break;
				case 2:
					lowlands++;
					break;
				case 1:
					waters++;
					break;
				case 0:
					noelem++;
					break;
				}
			}
			else
			{
				nomove++;
			}
			break;
		}
	}

	scope.moveToPnt(needCorrX, needCorrY);

	if (lowlands > 5 - nomove) scope.set_elem(lowland);
	else if (middlelands > 5 - nomove) scope.set_elem(midland);
	else if (highlands > 5 - nomove) scope.set_elem(highland);
	else if (mounts > 5 - nomove) scope.set_elem(mountain);
	else return false;
	return true;
	
}

void newTerrane::saveTerrane()
{
	std::string directory = "savedlands\\";
	std::string format = ".png";
	std::string filename = directory + this->getName() + format;

	settings.antialiasingLevel = 0;

	Image savedmap;

	savedmap.create(terrSize, terrSize, Color::Black);

	for (int i = 0; i < terrSize; i++)
	{
		for (int j = 0; j < terrSize; j++)
		{
			scope.moveToPnt(j, i);

			switch (scope.get_elem())
			{
			case water:
				savedmap.setPixel(j, i, Color(2, 2, 2));
				break;
			case lowland:
				savedmap.setPixel(j, i, Color(4, 4, 4));
				break;
			case midland:
				savedmap.setPixel(j, i, Color(5, 5, 5));
				break;
			case highland:
				savedmap.setPixel(j, i, Color(7, 7, 7));
				break;
			case cliff:
				savedmap.setPixel(j, i, Color(10, 10, 10));
				break;
			case mountain:
				savedmap.setPixel(j, i, Color(10, 10, 10));
				break;
			}
		}
	}

	if (!savedmap.saveToFile(filename))
	{
		cout << "Saving cancel" << endl;
	}
	else
	{
		cout << "Saving completed" << endl;
	}
}

bool newTerrane::loadTerrane()
{
	cout << "List of landnames for load:" << endl;
	cout << endl;
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	wstring buff[100];
	unsigned short chkc = 0;
	hf = FindFirstFile(L"savedlands\\*.land", &FindFileData);
	if (hf != INVALID_HANDLE_VALUE)
	{
		do
		{
			wstring nameOfFile = FindFileData.cFileName;
			wstring ch = nameOfFile.erase(nameOfFile.length() - 5);
			wcout << ch << endl;
			buff[chkc] = ch;
			wcout << endl;
			chkc++;
		}while (FindNextFile(hf, &FindFileData) != 0);
		ifstream loadedland;
		wstring direct = L"savedlands\\";
		wstring format = L".land";
		wstring landname;
		cout << "Enter name of loaded land" << endl;
		cout << endl;
		wcin >> landname;
		bool check = false;
		for (unsigned short k = 0; k < chkc; k++)
		{
			if (buff[k] == landname) { check = true; }
		}
		if (check == true)
		{
			wstring loadlandpath = direct + landname + format;
			loadedland.open(loadlandpath);
			if (!loadedland) 
			{
				cout << "File not found!" << endl; 
				FindClose(hf);
				return false;
			}
			else
			{
				unsigned short terrResize = 0;
				string rename;
				loadedland >> terrResize;
				loadedland >> rename;
				if (terrResize > 512) 
				{ 
					cout << "Warning! Wrong size!" << endl; 
					FindClose(hf);
					return false;
				}
				terrSize = terrResize;
				name = rename;
				for (unsigned short i = 0; i < terrSize; i++)
				{
					for (unsigned short j = 0; j < terrSize; j++)
					{
						unsigned short buf = 0;
						char* cbuf = new char;
						loadedland.read(cbuf, 1);
						while (*cbuf != '1' && *cbuf != '2' && *cbuf != '3' && *cbuf != '4' && *cbuf != '5' && *cbuf != '6')
						{
							loadedland.read(cbuf, 1);
						}
						buf = *cbuf - '0';
						scope.moveToPnt(j, i);
						scope.set_elem(buf);
						delete cbuf;
					}
				}
				loadedland.close();
				this->climateZoneConstructor();
				this->forest_generate();
				this->biomeConstructor();
				cout << "Loading land, named " << name << ", complete." << endl;
				cout << endl;
				FindClose(hf);
				return true;
			}
		}
		else
		{
			cout << "Wrong file name" << endl;
			FindClose(hf);
			return false;
		}
	}
	else
	{
		cout << "Files for loading not found!" << endl;
		FindClose(hf);
		return false;
	}
	FindClose(hf);
}

void newTerrane::reSetTerrane(short rterr, string rname)
{
	if (rterr > 8160) { cout << "Warning! Wrong size!" << endl; exit(0); }
	name = rname;
	terrSize = rterr - 1;
	scope.remakeField(terrSize);
	forest.remakeField(terrSize);
	//civilization.remakeField(terrSize);
	climat_zone.remakeField(terrSize);
	biome.remakeField(terrSize);
	//zone_name.remakeField(terrSize);
	//resourses.remakeField(terrSize);
}

int newTerrane::getScopeLineSize()
{
	return terrSize;
}

auto newTerrane::getScopeElem(short x, short y)
{
	scope.moveToPnt(x, y);
	return scope.get_elem();
}

auto newTerrane::getForestElem(short x, short y)
{
	forest.moveToPnt(x, y);
	return forest.get_elem();
}

auto newTerrane::getCivilizationElem(short x, short y)
{
	//civilization.moveToPnt(x, y);
	//return civilization.get_elem();
}

auto newTerrane::getClimat_zoneElem(short x, short y)
{
	climat_zone.moveToPnt(x, y);
	return climat_zone.get_elem();
}

auto newTerrane::getBiomeElem(short x, short y)
{
	biome.moveToPnt(x, y);
	return biome.get_elem();
}

auto newTerrane::getZone_nameElem(short x, short y)
{
	//zone_name.moveToPnt(x, y);
	//return zone_name.get_elem();
}

auto newTerrane::getResoursesElem(short x, short y)
{
	//resourses.moveToPnt(x, y);
	//return resourses.get_elem();
}

bool newTerrane::ScopeScaner(short target, short numOfCykles, short ignore, short worktype)
{
	short red = numOfCykles - 1;
	short ign = ignore - 1;
	short targetcheck = 0;
	bool Scanresult = false;
	short sum = 0;
	for (unsigned short ik = 0; ik < red; ik++)
	{
		short right = ik;
		short up = ik;
		short left = ik+1;
		short down = ik+1;
		bool right_moved = scope.move_right();
		if (right_moved == true)
		{
			if (scope.get_elem() == target)
			{
				if (ik < ign)
				{
					return false;
				}
				else
				{
					Scanresult = true;
					targetcheck++;
				}
				if (worktype == 0)
				{
					return true;
				}
			}
			left++;
		}
		else
		{

		}
		for (unsigned short jk = 0; jk < up; jk++)
		{
			bool up_moved = scope.move_up();
			if (up_moved == true)
			{
				if (scope.get_elem() == target)
				{
					if (ik < ign)
					{
						return false;
					}
					else
					{
						Scanresult = true;
						targetcheck++;
					}
					if (worktype == 0)
					{
						return true;
					}
				}
				down++;
			}
			else
			{
			}
		}
		for (unsigned short jh = 0; jh < left; jh++)
		{
			bool left_moved = scope.move_left();
			if (left_moved == true)
			{
				if (scope.get_elem() == target)
				{
					if (ik < ign)
					{
						return false;
					}
					else
					{
						Scanresult = true;
						targetcheck++;
					}
					if (worktype == 0)
					{
						return true;
					}
				}
				right++;
			}
		}

		for (unsigned short jf = 0; jf < down; jf++)
		{
			bool down_moved = scope.move_down();
			if (down_moved == true)
			{
				if (scope.get_elem() == target)
				{
					if (ik < ign)
					{
						return false;
					}
					else
					{
						Scanresult = true;
						targetcheck++;
					}
					if (worktype == 0)
					{
						return true;
					}
				}
				up++;
			}
		}

		for (unsigned short jd = 0; jd < right; jd++)
		{
			bool right_moved = scope.move_right();
			if (right_moved == true)
			{
				if (scope.get_elem() == target)
				{
					if (ik < ign)
					{
						return false;
					}
					else
					{
						Scanresult = true;
						targetcheck++;
					}
					if (worktype == 0)
					{
						return true;
					}
				}
			}
		}
	}

	sum = numOfCykles * 8;

	if (worktype == 0)
	{
		return Scanresult;
	}
	else
	{
		if (targetcheck == sum)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

bool newTerrane::ClimateScaner(short target, short numOfCykles, short ignore, short worktype)
{
	short red = numOfCykles - 1;
	short ign = ignore - 1;
	short targetcheck = 0;
	bool Scanresult = false;
	short sum = 0;
	for (unsigned short ik = 0; ik < red; ik++)
	{
		short right = ik;
		short up = ik;
		short left = ik + 1;
		short down = ik + 1;
		bool right_moved = climat_zone.move_right();
		if (right_moved == true)
		{
			if (climat_zone.get_elem() == target)
			{
				if (ik == ign)
				{
					return false;
				}
				else
				{
					Scanresult = true;
					targetcheck++;
				}
			}
			left++;
		}
		else
		{

		}
		for (unsigned short jk = 0; jk < up; jk++)
		{
			bool up_moved = climat_zone.move_up();
			if (up_moved == true)
			{
				if (climat_zone.get_elem() == target)
				{
					if (ik == ign)
					{
						return false;
					}
					else
					{
						Scanresult = true;
						targetcheck++;
					}
				}
				down++;
			}
			else
			{
			}
		}
		for (unsigned short jh = 0; jh < left; jh++)
		{
			bool left_moved = climat_zone.move_left();
			if (left_moved == true)
			{
				if (climat_zone.get_elem() == target)
				{
					if (ik == ign)
					{
						return false;
					}
					else
					{
						Scanresult = true;
						targetcheck++;
					}
				}
				right++;
			}
		}

		for (unsigned short jf = 0; jf < down; jf++)
		{
			bool down_moved = climat_zone.move_down();
			if (down_moved == true)
			{
				if (climat_zone.get_elem() == target)
				{
					if (ik == ign)
					{
						return false;
					}
					else
					{
						Scanresult = true;
						targetcheck++;
					}
				}
				up++;
			}
		}

		for (unsigned short jd = 0; jd < right; jd++)
		{
			bool right_moved = climat_zone.move_right();
			if (right_moved == true)
			{
				if (climat_zone.get_elem() == target)
				{
					if (ik == ign)
					{
						return false;
					}
					else
					{
						Scanresult = true;
						targetcheck++;
					}
				}
			}
		}
		sum = numOfCykles * 8;
	}
	if (worktype == 0)
	{
		return Scanresult;
	}
	else
	{
		if (targetcheck == sum)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool newTerrane::BiomeScaner(short target, short numOfCykles, short ignore, short worktype)
{
	short red = numOfCykles - 1;
	short ign = ignore - 1;
	short targetcheck = 0;
	bool Scanresult = false;
	short sum = 0;
	for (unsigned short ik = 0; ik < red; ik++)
	{
		short right = ik;
		short up = ik;
		short left = ik + 1;
		short down = ik + 1;
		bool right_moved = biome.move_right();
		if (right_moved == true)
		{
			if (biome.get_elem() == target)
			{
				if (ik == ign)
				{
					return false;
				}
				else
				{
					Scanresult = true;
					targetcheck++;
				}
			}
			left++;
		}
		else
		{

		}
		for (unsigned short jk = 0; jk < up; jk++)
		{
			bool up_moved = biome.move_up();
			if (up_moved == true)
			{
				if (biome.get_elem() == target)
				{
					if (ik == ign)
					{
						return false;
					}
					else
					{
						Scanresult = true;
						targetcheck++;
					}
				}
				down++;
			}
			else
			{
			}
		}
		for (unsigned short jh = 0; jh < left; jh++)
		{
			bool left_moved = biome.move_left();
			if (left_moved == true)
			{
				if (biome.get_elem() == target)
				{
					if (ik == ign)
					{
						return false;
					}
					else
					{
						Scanresult = true;
						targetcheck++;
					}
				}
				right++;
			}
		}

		for (unsigned short jf = 0; jf < down; jf++)
		{
			bool down_moved = biome.move_down();
			if (down_moved == true)
			{
				if (biome.get_elem() == target)
				{
					if (ik == ign)
					{
						return false;
					}
					else
					{
						Scanresult = true;
						targetcheck++;
					}
				}
				up++;
			}
		}

		for (unsigned short jd = 0; jd < right; jd++)
		{
			bool right_moved = biome.move_right();
			if (right_moved == true)
			{
				if (biome.get_elem() == target)
				{
					if (ik == ign)
					{
						return false;
					}
					else
					{
						Scanresult = true;
						targetcheck++;
					}
				}
			}
		}
		sum = numOfCykles * 8;
	}
	if (worktype == 0)
	{
		return Scanresult;
	}
	else
	{
		if (targetcheck == sum)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

void newTerrane::mountainesGenerator()
{
	cout << "Generating mountains" << endl;
	mountains = d8.randomize(6)-1;
	twoPoints arrMount[6];
	for (int i = 0; i < mountains; i++)
	{
		int a = d8.randomize(terrSize) - 1;
		int b = d8.randomize(terrSize) - 1;
		scope.moveToPnt(a, b);
		scope.set_elem(6);
		twoPoints ptrn(a, b);
		arrMount[i].setPoints(ptrn.get_pnt1(), ptrn.get_pnt2());
	}
	for (int i = 0; i < mountains; i++)
	{
		int tx = arrMount[i].get_pnt1();
		int ty = arrMount[i].get_pnt2();
		scope.moveToPnt(tx, ty);
		int moveTo = d8.randomize(8);
		int limit = (terrSize / d8.randomize(6)) / 2;
		switch (moveTo)
		{
		case 1:
			scope.move_down();
			scope.set_elem(6);
			for (int j = 0; j < limit; j++)
			{
				int var = d8.randomize(3);
				switch (var)
				{
				case 1:
					scope.move_down();
					scope.set_elem(6);
					break;
				case 2:
					scope.move_downl();
					scope.set_elem(6);
					break;
				case 3:
					scope.move_downr();
					scope.set_elem(6);
					break;
				}
			}
			scope.moveToPnt(tx, ty);
			scope.move_up();
			scope.set_elem(6);
			for (int j = 0; j < limit; j++)
			{
				int var = d8.randomize(3);
				switch (var)
				{
				case 1:
					scope.move_up();
					scope.set_elem(6);
					break;
				case 2:
					scope.move_upl();
					scope.set_elem(6);
					break;
				case 3:
					scope.move_upr();
					scope.set_elem(6);
					break;
				}
			}
			break;
		case 2:
			scope.move_left();
			scope.set_elem(6);
			for (int j = 0; j < limit; j++)
			{
				int var = d8.randomize(3);
				switch (var)
				{
				case 1:
					scope.move_left();
					scope.set_elem(6);
					break;
				case 2:
					scope.move_upl();
					scope.set_elem(6);
					break;
				case 3:
					scope.move_downl();
					scope.set_elem(6);
					break;
				}
			}
			scope.moveToPnt(tx, ty);
			scope.move_right();
			scope.set_elem(6);
			for (int j = 0; j < limit; j++)
			{
				int var = d8.randomize(3);
				switch (var)
				{
				case 1:
					scope.move_right();
					scope.set_elem(6);
					break;
				case 2:
					scope.move_upr();
					scope.set_elem(6);
					break;
				case 3:
					scope.move_downl();
					scope.set_elem(6);
					break;
				}
			}
			break;
		case 3:
			scope.move_up();
			scope.set_elem(6);
			for (int j = 0; j < limit; j++)
			{
				int var = d8.randomize(3);
				switch (var)
				{
				case 1:
					scope.move_up();
					scope.set_elem(6);
					break;
				case 2:
					scope.move_upl();
					scope.set_elem(6);
					break;
				case 3:
					scope.move_upr();
					scope.set_elem(6);
					break;
				}
			}
			scope.moveToPnt(tx, ty);
			scope.move_down();
			scope.set_elem(6);
			for (int j = 0; j < limit; j++)
			{
				int var = d8.randomize(3);
				switch (var)
				{
				case 1:
					scope.move_down();
					scope.set_elem(6);
					break;
				case 2:
					scope.move_downl();
					scope.set_elem(6);
					break;
				case 3:
					scope.move_downr();
					scope.set_elem(6);
					break;
				}
			}
			break;
		case 4:
			scope.move_right();
			scope.set_elem(6);
			for (int j = 0; j < limit; j++)
			{
				int var = d8.randomize(3);
				switch (var)
				{
				case 1:
					scope.move_right();
					scope.set_elem(6);
					break;
				case 2:
					scope.move_upr();
					scope.set_elem(6);
					break;
				case 3:
					scope.move_downl();
					scope.set_elem(6);
					break;
				}
			}
			scope.moveToPnt(tx, ty);
			scope.move_left();
			scope.set_elem(6);
			for (int j = 0; j < limit; j++)
			{
				int var = d8.randomize(3);
				switch (var)
				{
				case 1:
					scope.move_left();
					scope.set_elem(6);
					break;
				case 2:
					scope.move_upl();
					scope.set_elem(6);
					break;
				case 3:
					scope.move_downl();
					scope.set_elem(6);
					break;
				}
			}
			break;
		case 5:
			scope.move_downr();
			scope.set_elem(6);
			for (int j = 0; j < limit; j++)
			{
				int var = d8.randomize(3);
				switch (var)
				{
				case 1:
					scope.move_downr();
					scope.set_elem(6);
					break;
				case 2:
					scope.move_down();
					scope.set_elem(6);
					break;
				case 3:
					scope.move_right();
					scope.set_elem(6);
					break;
				}
			}
			scope.moveToPnt(tx, ty);
			scope.move_upl();
			scope.set_elem(6);
			for (int j = 0; j < limit; j++)
			{
				int var = d8.randomize(3);
				switch (var)
				{
				case 1:
					scope.move_upl();
					scope.set_elem(6);
					break;
				case 2:
					scope.move_up();
					scope.set_elem(6);
					break;
				case 3:
					scope.move_right();
					scope.set_elem(6);
					break;
				}
			}
			break;
		case 6:
			scope.move_downl();
			scope.set_elem(6);
			for (int j = 0; j < limit; j++)
			{
				int var = d8.randomize(3);
				switch (var)
				{
				case 1:
					scope.move_downl();
					scope.set_elem(6);
					break;
				case 2:
					scope.move_down();
					scope.set_elem(6);
					break;
				case 3:
					scope.move_left();
					scope.set_elem(6);
					break;
				}
			}
			scope.moveToPnt(tx, ty);
			scope.move_upr();
			scope.set_elem(6);
			for (int j = 0; j < limit; j++)
			{
				int var = d8.randomize(3);
				switch (var)
				{
				case 1:
					scope.move_upr();
					scope.set_elem(6);
					break;
				case 2:
					scope.move_up();
					scope.set_elem(6);
					break;
				case 3:
					scope.move_right();
					scope.set_elem(6);
					break;
				}
			}
			break;
		case 7:
			scope.move_upr();
			scope.set_elem(6);
			for (int j = 0; j < limit; j++)
			{
				int var = d8.randomize(3);
				switch (var)
				{
				case 1:
					scope.move_upr();
					scope.set_elem(6);
					break;
				case 2:
					scope.move_up();
					scope.set_elem(6);
					break;
				case 3:
					scope.move_right();
					scope.set_elem(6);
					break;
				}
			}
			scope.moveToPnt(tx, ty);
			scope.move_downl();
			scope.set_elem(6);
			for (int j = 0; j < limit; j++)
			{
				int var = d8.randomize(3);
				switch (var)
				{
				case 1:
					scope.move_downl();
					scope.set_elem(6);
					break;
				case 2:
					scope.move_down();
					scope.set_elem(6);
					break;
				case 3:
					scope.move_left();
					scope.set_elem(6);
					break;
				}
			}
			break;
		case 8:
			scope.move_upl();
			scope.set_elem(6);
			for (int j = 0; j < limit; j++)
			{
				int var = d8.randomize(3);
				switch (var)
				{
				case 1:
					scope.move_upl();
					scope.set_elem(6);
					break;
				case 2:
					scope.move_up();
					scope.set_elem(6);
					break;
				case 3:
					scope.move_right();
					scope.set_elem(6);
					break;
				}
			}
			scope.moveToPnt(tx, ty);
			scope.move_downr();
			scope.set_elem(6);
			for (int j = 0; j < limit; j++)
			{
				int var = d8.randomize(3);
				switch (var)
				{
				case 1:
					scope.move_downr();
					scope.set_elem(6);
					break;
				case 2:
					scope.move_down();
					scope.set_elem(6);
					break;
				case 3:
					scope.move_right();
					scope.set_elem(6);
					break;
				}
			}
			break;
		}
	}
	cout << "Mountains complete" << endl;
}

void newTerrane::frameConstructor(short a)
{
	for (short i = 0; i < terrSize; i++)
	{
		scope.moveToPnt(0, i);
		scope.set_elem(1);
		if (i == 0)
		{
			scope.move_down();
			scope.set_elem(a);
			scope.move_right();
			scope.set_elem(a);
			scope.move_up();
			scope.set_elem(a);
		}
		if (i == terrSize - 1)
		{
			scope.move_up();
			scope.set_elem(a);
			scope.move_right();
			scope.set_elem(a);
			scope.move_down();
			scope.set_elem(a);
		}
		scope.moveToPnt(i, 0);
		scope.set_elem(a);
		scope.moveToPnt(terrSize - 1, i);
		scope.set_elem(a);
		if (i == 0)
		{
			scope.move_down();
			scope.set_elem(a);
			scope.move_left();
			scope.set_elem(a);
			scope.move_up();
			scope.set_elem(a);
		}
		if (i == terrSize - 1)
		{
			scope.move_up();
			scope.set_elem(a);
			scope.move_left();
			scope.set_elem(a);
			scope.move_down();
			scope.set_elem(a);
		}
		scope.moveToPnt(i, terrSize - 1);
		scope.set_elem(a);
	}
}

void newTerrane::set_numberOfContinents(int continents)
{
	numOfContinents = continents;
}

void newTerrane::zeroDelete(short a)
{
	for (int i = 0; i < terrSize; i++)
	{
		for (int j = 0; j < terrSize; j++)
		{
			scope.moveToPnt(j, i);
			int raw = scope.get_elem();
			if (raw == 0)
			{
				scope.set_elem(a);
			}
			else
			{
			}
		}
	}
}

short newTerrane::typeOfLandVariator(short target, short solid, const char worktype[])
{
	if (target == 0 && worktype == "randomize")
	{
		int randG = d8.randomize(1000)/10;
		switch (solid)
		{
		case mountain:
			if (randG > 93)
			{
				return mountain;
			}
			else
			{
				return highland;
			}
			break;
		case highland:
			if (randG > 67)
			{
				return highland;
			}
			else
			{
				return midland;
			}
			break;
		case midland:
			if (randG > 46)
			{
				return midland;
			}
			else
			{
				return lowland;
			}
			break;
		case lowland:
			if (randG > 36)
			{
				return lowland;
			}
			else
			{
				if (percentOfWater > 97)
				{
					return water;
				}
				else
				{
					return midland;
				}
			}
			break;
		case water:
			if (randG > 96)
			{
				return water;
			}
			else
			{
				if (percentOfWater > 97)
				{
					return water;
				}
				else
				{
					return lowland;
				}
			}
			break;
		default:
			return 0;
		}
	}
	else if (target == 0 && worktype != "randomize")
	{
		int randG = d8.randomize(100);
		if (randG > 60)
		{
			return solid;
		}
		else
		{
			return target;
		}
	}
	else
	{
		return target;
	}
}

short newTerrane::typeOfLandRelocator(short target, short solid)
{
	switch (solid)
	{
	case water:
		if (target == midland || target == highland)
		{
			if (percentOfWater > 97 && d8.randomize(100) > 10)
			{
				return water;
			}
			else
			{
				return lowland;
			}
		}
		//else if (target == 6)
		//{
		//	return(5);
		//}
		else if(target == nowidth)
		{
			if (percentOfWater > 97 && d8.randomize(100) > 10)
			{
				return water;
			}
			else
			{
				return solid;
			}
		}
		break;
	case lowland:
		if (target == highland)
		{
			if (percentOfWater > 97 && d8.randomize(100) > 10)
			{
				return water;
			}
			else
			{
				return midland;
			}
		}
		//else if (target == 6)
		//{
		//	return(5);
		//}
		else if(target == nowidth)
		{
			if (percentOfWater > 97 && d8.randomize(100) > 10)
			{
				return water;
			}
			else
			{
				return solid;
			}
		}
		break;
	case midland:
		if (target == mountain)
		{
			if (percentOfWater > 97 && d8.randomize(100) > 10)
			{
				return water;
			}
			else
			{
				return highland;
			}
		}
		else if(target == water)
		{
			if (percentOfWater > 97 && d8.randomize(100) > 10)
			{
				return water;
			}
			else
			{
				return lowland;
			}
		}
		else if (target == nowidth)
		{
			if (percentOfWater > 97 && d8.randomize(100) > 10)
			{
				return water;
			}
			else
			{
				return solid;
			}
		}
		break;
	case highland:
		if (target == lowland)
		{
			if (percentOfWater > 97 && d8.randomize(100) > 10)
			{
				return water;
			}
			else
			{
				return midland;
			}
		}
		//else if (target == 5)
		//{
		//	return(6);
		//}
		else if (target == nowidth)
		{
			if (percentOfWater > 97 && d8.randomize(100) > 10)
			{
				return water;
			}
			else
			{
				return solid;
			}
		}
		break;
	case cliff:
		if (target == highland)
		{
			if (percentOfWater > 97 && d8.randomize(100) > 10)
			{
				return water;
			}
			else
			{
				return mountain;
			}
		}
		//else if (target == 5)
		//{
		//	bool water_check = this->LandscapeScaner(1, 1, 2);

		//	if (water_check == false)
		//	{
		//		return(6);
		//	}

		//}
		else if (target == nowidth)
		{
			if (percentOfWater > 97 && d8.randomize(100) > 10)
			{
				return water;
			}
			else
			{
				return solid;
			}
		}
		break;
	case mountain:
		if (target == lowland || target == midland)
		{
			if (percentOfWater > 97 && d8.randomize(100) > 10)
			{
				return water;
			}
			else
			{
				return highland;
			}
		}
		//else if (target == 1)
		//{
		//	return 5;
		//}
		else if (target == nowidth)
		{
			if (percentOfWater > 97 && d8.randomize(100) > 10)
			{
				return water;
			}
			else
			{
				return solid;
			}
		}
		break;
	default:
			return target;
	}
}

bool newTerrane::climateZoneConstructor()
{
	int equator = 1;
	int completeCheker = 0;
	if (terrSize%2 == 0)
	{
		equator = 2;
	}
	for (int i = 0; i < equator; i++)
	{
		int y = terrSize / 2 + i;
		for (int x = 0; x < terrSize; x++)
		{
			climat_zone.moveToPnt(x, y);
			climat_zone.set_elem(equatorial);
		}
	}
	completeCheker++;
	int chek = terrSize / 80;
	for (int i = 0; i < chek; i++)
	{
		int py = terrSize / 2 + (equator - 1) + completeCheker;
		int my = terrSize / 2 - completeCheker;
		for (int x = 0; x < terrSize; x++)
		{
			climat_zone.moveToPnt(x, py);
			climat_zone.set_elem(equatorial);
			climat_zone.moveToPnt(x, my);
			climat_zone.set_elem(equatorial);
		}
		completeCheker++;
	}
	chek = terrSize / 30 + 1;
	for (int y = 0; y < chek; y++)
	{
		int py = terrSize / 2 + (equator - 1) + completeCheker;
		int my = terrSize / 2 - completeCheker;
		for (int x = 0; x < terrSize; x++)
		{
			climat_zone.moveToPnt(x, py);
			climat_zone.set_elem(subequatorial);
			climat_zone.moveToPnt(x, my);
			climat_zone.set_elem(subequatorial);
		}
		completeCheker++;
	}
	chek = terrSize / 25 + 1;
	for (int y = 0; y < chek; y++)
	{
		int py = terrSize / 2 + (equator - 1) + completeCheker;
		int my = terrSize / 2 - completeCheker;
		for (int x = 0; x < terrSize; x++)
		{
			climat_zone.moveToPnt(x, py);
			climat_zone.set_elem(tropical);
			climat_zone.moveToPnt(x, my);
			climat_zone.set_elem(tropical);
		}
		completeCheker++;
	}
	chek = terrSize / 11 + 1;
	for (int y = 0; y < chek; y++)
	{
		int py = terrSize / 2 + (equator - 1) + completeCheker;
		int my = terrSize / 2 - completeCheker;
		for (int x = 0; x < terrSize; x++)
		{
			climat_zone.moveToPnt(x, py);
			climat_zone.set_elem(subtropical);
			climat_zone.moveToPnt(x, my);
			climat_zone.set_elem(subtropical);
		}
		completeCheker++;
	}
	chek = terrSize / 5 + 1;
	for (int y = 0; y < chek; y++)
	{
		int py = terrSize / 2 + (equator - 1) + completeCheker;
		int my = terrSize / 2 - completeCheker;
		for (int x = 0; x < terrSize; x++)
		{
			climat_zone.moveToPnt(x, py);
			climat_zone.set_elem(temperate);
			climat_zone.moveToPnt(x, my);
			climat_zone.set_elem(temperate);
		}
		completeCheker++;
	}
	chek = terrSize / 20 + 1;
	for (int y = 0; y < chek; y++)
	{
		int py = terrSize / 2 + (equator - 1) + completeCheker;
		int my = terrSize / 2 - completeCheker;
		for (int x = 0; x < terrSize; x++)
		{
			climat_zone.moveToPnt(x, py);
			climat_zone.set_elem(thundra);
			climat_zone.moveToPnt(x, my);
			climat_zone.set_elem(thundra);
		}
		completeCheker++;
	}
	while (completeCheker < terrSize/2)
	{
		int py = terrSize / 2 + (equator - 1) + completeCheker;
		int my = terrSize / 2 - completeCheker;
		for (int x = 0; x < terrSize; x++)
		{
			climat_zone.moveToPnt(x, py);
			climat_zone.set_elem(arctic);
			climat_zone.moveToPnt(x, my);
			climat_zone.set_elem(arctic);
		}
		completeCheker++;
	}
	for (int x = 0; x < terrSize; x++)
	{
		climat_zone.moveToPnt(x, 0);
		climat_zone.set_elem(arctic);
		climat_zone.moveToPnt(x, terrSize-1);
		climat_zone.set_elem(arctic);
	}
	return true;
}

short newTerrane::set_percentOfWater(short a)
{
	if(a > 100)
	{
		percentOfWater = 100;
	}
	else if (a < 0)
	{
		percentOfWater = 0;
	}
	else
	{
		percentOfWater = a;
	}
	return percentOfWater;
}

void newTerrane::biomeConstructor()
{
	for (int i = 0; i < terrSize; i++)
	{
		for (int j = 0; j < terrSize; j++)
		{
			scope.moveToPnt(j, i);
			forest.moveToPnt(j, i);
			biome.moveToPnt(j, i);
			climat_zone.moveToPnt(j, i);
			bool waterCheker = false;
			short scopetype = nowidth;
			short climatetype = noclimate;
			switch (scope.get_elem())
			{
				case water:
					switch (climat_zone.get_elem())
					{
					case arctic:
						biome.set_elem(icewater);
						break;
					case thundra:
						biome.set_elem(coldwater);
						break;
					case temperate:
						biome.set_elem(temperatewater);
						break;
					case subtropical:
						biome.set_elem(temperatewater);
						break;
					case tropical:
						biome.set_elem(warmwater);
						break;
					case subequatorial:
						biome.set_elem(warmwater);
						break;
					case equatorial:
						biome.set_elem(warmwater);
						break;
					}
					break;
				case lowland:
					switch (climat_zone.get_elem())
					{
					case arctic:
						biome.set_elem(arcticdesert);
						break;
					case thundra:
						if (this->ScopeScaner(water, 3, 0, 0) == true)
						{
							if (forest.get_elem() == true)
							{
								biome.set_elem(coldforest);
							}
							else
							{
								biome.set_elem(thundraswamp);
							}
						}
						else
						{
							biome.set_elem(thundrawasteland);
						}
						break;
					case temperate:
						if (this->ScopeScaner(water, 4, 0, 0) == true)
						{
							if (forest.get_elem() == true)
							{
								biome.set_elem(temperateforest);
							}
							else
							{
								biome.set_elem(swamp);
							}
						}
						else
						{
							biome.set_elem(wasteland);
						}
						break;
					case subtropical:
						if (this->ScopeScaner(water, 5, 0, 0) == true)
						{
							if (forest.get_elem() == true)
							{
								biome.set_elem(jungle);
							}
							else
							{
								biome.set_elem(swamp);
							}
						}
						else
						{
							biome.set_elem(steppe);
						}
						break;
					case tropical:
						if (this->ScopeScaner(water, 4, 0, 0) == true)
						{
							if (forest.get_elem() == true)
							{
								biome.set_elem(jungle);
							}
							else
							{
								biome.set_elem(oasis);
							}
						}
						else
						{
							biome.set_elem(steppe);
						}
						break;
					case subequatorial:
						if (this->ScopeScaner(water, 3, 0, 0) == true)
						{
							if (forest.get_elem() == true)
							{
								biome.set_elem(jungle);
							}
							else
							{
								biome.set_elem(oasis);
							}
						}
						else
						{
							biome.set_elem(desert);
						}
						break;
					case equatorial:
						if (this->ScopeScaner(water, 2, 0, 0) == true)
						{
							if (forest.get_elem() == true)
							{
								biome.set_elem(jungle);
							}
							else
							{
								biome.set_elem(oasis);
							}
						}
						else
						{
							biome.set_elem(desert);
						}
						break;
					}
					break;
				case midland:
					switch (climat_zone.get_elem())
					{
					case arctic:
						biome.set_elem(arcticdesert);
						break;
					case thundra:
						if (this->ScopeScaner(water, 3, 0, 0) == true)
						{
							if (forest.get_elem() == true)
							{
								biome.set_elem(coldforest);
							}
							else
							{
								biome.set_elem(thundrafield);
							}
						}
						else
						{
							biome.set_elem(thundrawasteland);
						}
						break;
					case temperate:
						if (this->ScopeScaner(water, 4, 0, 0) == true)
						{
							if (forest.get_elem() == true)
							{
								biome.set_elem(temperateforest);
							}
							else
							{
								biome.set_elem(valley);
							}
						}
						else
						{
							biome.set_elem(wasteland);
						}
						break;
					case subtropical:
						if (this->ScopeScaner(water, 5, 0, 0) == true)
						{
							if (forest.get_elem() == true)
							{
								biome.set_elem(jungle);
							}
							else
							{
								biome.set_elem(warmwalley);
							}
						}
						else
						{
							biome.set_elem(steppe);
						}
						break;
					case tropical:
						if (this->ScopeScaner(water, 4, 0, 0) == true)
						{
							if (forest.get_elem() == true)
							{
								biome.set_elem(jungle);
							}
							else
							{
								biome.set_elem(warmwalley);
							}
						}
						else
						{
							biome.set_elem(steppe);
						}
						break;
					case subequatorial:
						if (this->ScopeScaner(water, 3, 0, 0) == true)
						{
							if (forest.get_elem() == true)
							{
								biome.set_elem(jungle);
							}
							else
							{
								biome.set_elem(warmwalley);
							}
						}
						else
						{
							biome.set_elem(desert);
						}
						break;
					case equatorial:
						if (this->ScopeScaner(water, 2, 0, 0) == true)
						{
							if (forest.get_elem() == true)
							{
								biome.set_elem(jungle);
							}
							else
							{
								biome.set_elem(warmwalley);
							}
						}
						else
						{
							biome.set_elem(desert);
						}
						break;
					}
					break;
				case highland:
					switch (climat_zone.get_elem())
					{
					case arctic:
						biome.set_elem(arcticdesert);
						break;
					case thundra:
						if (this->ScopeScaner(water, 3, 0, 0) == true)
						{
							if (forest.get_elem() == true)
							{
								biome.set_elem(coldforest);
							}
							else
							{
								biome.set_elem(thundrafield);
							}
						}
						else
						{
							biome.set_elem(thundrawasteland);
						}
						break;
					case temperate:
						if (this->ScopeScaner(water, 4, 0, 0) == true)
						{
							if (forest.get_elem() == true)
							{
								biome.set_elem(temperateforest);
							}
							else
							{
								biome.set_elem(valley);
							}
						}
						else
						{
							biome.set_elem(wasteland);
						}
						break;
					case subtropical:
						if (this->ScopeScaner(water, 5, 0, 0) == true)
						{
							if (forest.get_elem() == true)
							{
								biome.set_elem(jungle);
							}
							else
							{
								biome.set_elem(warmwalley);
							}
						}
						else
						{
							biome.set_elem(steppe);
						}
						break;
					case tropical:
						if (this->ScopeScaner(water, 4, 0, 0) == true)
						{
							if (forest.get_elem() == true)
							{
								biome.set_elem(jungle);
							}
							else
							{
								biome.set_elem(warmwalley);
							}
						}
						else
						{
							biome.set_elem(steppe);
						}
						break;
					case subequatorial:
						if (this->ScopeScaner(water, 3, 0, 0) == true)
						{
							if (forest.get_elem() == true)
							{
								biome.set_elem(jungle);
							}
							else
							{
								biome.set_elem(warmwalley);
							}
						}
						else
						{
							biome.set_elem(desert);
						}
						break;
					case equatorial:
						if (this->ScopeScaner(water, 2, 0, 0) == true)
						{
							if (forest.get_elem() == true)
							{
								biome.set_elem(jungle);
							}
							else
							{
								biome.set_elem(warmwalley);
							}
						}
						else
						{
							biome.set_elem(desert);
						}
						break;
					}
					break;
				case cliff:
					switch (climat_zone.get_elem())
					{
					case arctic:
						break;
					case thundra:
						break;
					case temperate:
						break;
					case subtropical:
						break;
					case tropical:
						break;
					case subequatorial:
						break;
					case equatorial:
						break;
					}
					break;
				case mountain:
					switch (climat_zone.get_elem())
					{
					case arctic:
						biome.set_elem(icepike);
						break;
					case thundra:
						if (this->ScopeScaner(mountain, 1, 0, 1) == true)
						{
							biome.set_elem(vulcan);
						}
						else
						{
							if (this->BiomeScaner(vulcan, 1, 0, 0) == true)
							{
								biome.set_elem(magmapike);
							}
							else
							{
								biome.set_elem(icepike);
							}
						}
						break;
					case temperate:
						if (this->ScopeScaner(mountain, 1, 0, 1) == true)
						{
							biome.set_elem(vulcan);
						}
						else
						{
							if (this->BiomeScaner(vulcan, 1, 0, 0) == true)
							{
								biome.set_elem(magmapike);
							}
							else
							{
								biome.set_elem(icepike);
							}
						}
						break;
					case subtropical:
						if (this->ScopeScaner(mountain, 1, 0, 1) == true)
						{
							biome.set_elem(vulcan);
						}
						else
						{
							if (this->BiomeScaner(vulcan, 1, 0, 0) == true)
							{
								biome.set_elem(magmapike);
							}
							else
							{
								biome.set_elem(icepike);
							}
						}
						break;
					case tropical:
						if (this->ScopeScaner(mountain, 1, 0, 1) == true)
						{
							biome.set_elem(vulcan);
						}
						else
						{
							if (this->BiomeScaner(vulcan, 1, 0, 0) == true)
							{
								biome.set_elem(magmapike);
							}
							else
							{
								biome.set_elem(icepike);
							}
						}
						break;
					case subequatorial:
						if (this->ScopeScaner(mountain, 1, 0, 1) == true)
						{
							biome.set_elem(vulcan);
						}
						else
						{
							if (this->BiomeScaner(vulcan, 1, 0, 0) == true)
							{
								biome.set_elem(magmapike);
							}
							else
							{
								biome.set_elem(icepike);
							}
						}
						break;
					case equatorial:
						if (this->ScopeScaner(mountain, 1, 0, 1) == true)
						{
							biome.set_elem(vulcan);
						}
						else
						{
							if (this->BiomeScaner(vulcan, 1, 0, 0) == true)
							{
								biome.set_elem(magmapike);
							}
							else
							{
								biome.set_elem(icepike);
							}
						}
						break;
					}
					break;
			}
		}
	}
}

bool newTerrane::riverConstructor(int numOfRivers)
{
	unsigned int sizeOfArray = 0;
	bool riverEnd = false;
	for (int y = 0; y < terrSize; y++)
	{
		for (short x = 0; x < terrSize; x++)
		{
			scope.moveToPnt(x, y);
			if ((scope.get_elem() == highland , mountain) && (climat_zone.get_elem() != arctic, equatorial))
			{
				sizeOfArray++;
			}
		}
	}

	twoPoints *savedCoord = new twoPoints[sizeOfArray];
	int i = 0;
	for (int y = 0; y < terrSize; y++)
	{
		for (short x = 0; x < terrSize; x++)
		{
			scope.moveToPnt(x, y);
			if ((scope.get_elem() == highland || scope.get_elem() == mountain) && sizeOfArray > 0)
			{
				savedCoord[i].setPoints(scope.get_nowx(), scope.get_nowy());
			}
			i++;
		}
	}
	if (sizeOfArray < 2)
	{
		delete[] savedCoord;
		return false;
	}
	for (int f = 0; f < numOfRivers; f++)
	{
		int choose = d8.randomize(sizeOfArray - 1);

		if (scope.moveToPnt(savedCoord[choose].get_pnt1(), savedCoord[choose].get_pnt2()) == false) riverEnd = true;
		else
		{
			scope.set_elem(water);
		}

		int iterator = 0;
		int riverStream = 0;

		while (riverEnd == true)
		{
			int goTo = d8.randomize(30);

			if (iterator == 0)
			{
				goTo = d8.randomize(80);
				iterator++;
				if (goTo > 70) { scope.move_up() == false ? riverEnd = true : riverEnd = false, riverStream = 1; }
				else if (goTo > 60) { scope.move_upl() == false ? riverEnd = true : riverEnd = false, riverStream = 2; }
				else if (goTo > 50) { scope.move_left() == false ? riverEnd = true : riverEnd = false, riverStream = 3; }
				else if (goTo > 40) { scope.move_downl() == false ? riverEnd = true : riverEnd = false, riverStream = 4; }
				else if (goTo > 30) { scope.move_down() == false ? riverEnd = true : riverEnd = false, riverStream = 5; }
				else if (goTo > 20) { scope.move_downr() == false ? riverEnd = true : riverEnd = false, riverStream = 6; }
				else if (goTo > 10) { scope.move_right() == false ? riverEnd = true : riverEnd = false, riverStream = 7; }
				else if (goTo > 0) { scope.move_upr() == false ? riverEnd = true : riverEnd = false, riverStream = 8; }
			}
			else
			{
				short red = 20;
				if (iterator < 20)
				{
					red = iterator;
				}

				if (riverStream == 1)
				{
					if (goTo > 20)
					{
						for (int i = 0; i < red; i++)
						{
							scope.move_upl() == true ? riverEnd = false : riverEnd = true;
						}
					}
					else if (goTo > 10)
					{
						for (int i = 0; i < red; i++)
						{
							scope.move_up() == true ? riverEnd = false : riverEnd = true;
						}
					}
					else
					{
						for (int i = 0; i < red; i++)
						{
							scope.move_upr() == true ? riverEnd = false : riverEnd = true;
						}
					}
				}
				else if (riverStream == 2)
				{
					if (goTo > 20)
					{
						for (int i = 0; i < red; i++)
						{
							scope.move_upl() == true ? riverEnd = false : riverEnd = true;
						}
					}
					else if (goTo > 10)
					{
						for (int i = 0; i < red; i++)
						{
							scope.move_up() == true ? riverEnd = false : riverEnd = true;
						}
					}
					else 
					{ 
						for (int i = 0; i < red; i++)
						{
							scope.move_left() == true ? riverEnd = false : riverEnd = true;
						}
					}
				}
				else if (riverStream == 3)
				{
					if (goTo > 20)
					{
						for (int i = 0; i < red; i++)
						{
							scope.move_upl() == true ? riverEnd = false : riverEnd = true;
						}
					}
					else if (goTo > 10)
					{
						for (int i = 0; i < red; i++)
						{
							scope.move_left() == true ? riverEnd = false : riverEnd = true;
						}
					}
					else 
					{ 
						for (int i = 0; i < red; i++)
						{
							scope.move_downl() == true ? riverEnd = false : riverEnd = true;
						}
					}
				}
				else if (riverStream == 4)
				{
					if (goTo > 20)
					{
						for (int i = 0; i < red; i++)
						{
							scope.move_left() == true ? riverEnd = false : riverEnd = true;
						}
					}
					else if (goTo > 10)
					{
						for (int i = 0; i < red; i++)
						{
							scope.move_downl() == true ? riverEnd = false : riverEnd = true;
						}
					}
					else 
					{ 
						for (int i = 0; i < red; i++)
						{
							scope.move_down() == true ? riverEnd = false : riverEnd = true;
						}
					}
				}
				else if (riverStream == 5)
				{
					if (goTo > 20)
					{
						for (int i = 0; i < red; i++)
						{
							scope.move_downl() == true ? riverEnd = false : riverEnd = true;
						}
					}
					else if (goTo > 10)
					{
						for (int i = 0; i < red; i++)
						{
							scope.move_down() == true ? riverEnd = false : riverEnd = true;
						}
					}
					else
					{
						for (int i = 0; i < red; i++)
						{
							scope.move_downr() == true ? riverEnd = false : riverEnd = true;
						}
					}
				}
				else if (riverStream == 6)
				{
					if (goTo > 20)
					{
						for (int i = 0; i < red; i++)
						{
							scope.move_down() == true ? riverEnd = false : riverEnd = true;
						}
					}
					else if (goTo > 10)
					{
						for (int i = 0; i < red; i++)
						{
							scope.move_downr() == true ? riverEnd = false : riverEnd = true;
						}
					}
					else
					{
						for (int i = 0; i < red; i++)
						{
							scope.move_right() == true ? riverEnd = false : riverEnd = true;
						}
					}
				}
				else if (riverStream == 7)
				{
					if (goTo > 20)
					{
						for (int i = 0; i < red; i++)
						{
							scope.move_downr() == true ? riverEnd = false : riverEnd = true;
						}
					}
					else if (goTo > 10)
					{
						for (int i = 0; i < red; i++)
						{
							scope.move_right() == true ? riverEnd = false : riverEnd = true;
						}
					}
					else 
					{ 
						for (int i = 0; i < red; i++)
						{
							scope.move_upr() == true ? riverEnd = false : riverEnd = true;
						}
					}
				}
				else if (riverStream == 8)
				{
					if (goTo > 20)
					{
						for (int i = 0; i < red; i++)
						{
							scope.move_right() == true ? riverEnd = false : riverEnd = true;
						}
					}
					else if (goTo > 10)
					{
						for (int i = 0; i < red; i++)
						{
							scope.move_up() == true ? riverEnd = false : riverEnd = true;
						}
					}
					else 
					{ 
						for (int i = 0; i < red; i++)
						{
							scope.move_upr() == true ? riverEnd = false : riverEnd = true;
						}

					}
				}
				else riverEnd = true;
				scope.get_elem() != water ? scope.set_elem(water) : 0;
				int x = scope.get_nowx();
				int y = scope.get_nowy();
				bool end = false;
				short sum = 0;
				for (unsigned short ik = 0; ik < red; ik++)
				{
					short right = ik;
					short up = ik;
					short left = ik + 1;
					short down = ik + 1;
					bool right_moved = scope.move_right();
					if (right_moved == true)
					{
						scope.get_elem() != water ? scope.set_elem(water) : 0;
						left++;
					}
					for (unsigned short jk = 0; jk < up; jk++)
					{
						bool up_moved = scope.move_up();
						if (up_moved == true)
						{
							scope.get_elem() != water ? scope.set_elem(water) : 0;
							down++;
						}
					}
					for (unsigned short jh = 0; jh < left; jh++)
					{
						bool left_moved = scope.move_left();
						if (left_moved == true)
						{
							scope.get_elem() != water ? scope.set_elem(water) : 0;
							right++;
						}
					}

					for (unsigned short jf = 0; jf < down; jf++)
					{
						bool down_moved = scope.move_down();
						if (down_moved == true)
						{
							scope.get_elem() != water ? scope.set_elem(water) : 0;
							up++;
						}
					}

					for (unsigned short jd = 0; jd < right; jd++)
					{
						bool right_moved = scope.move_right();
						if (right_moved == true)
						{	
							scope.get_elem() != water ? scope.set_elem(water) : 0;
						}
					}
					sum = iterator * 8;
				}
				scope.moveToPnt(x, y);
				iterator++;
			}
		}
	}
	delete[] savedCoord;
	return false;
}

void newTerrane::contconstr()
{
	int sizeOfSegment = terrSize / numOfContinents;
	twoPoints arrayOfSegments[20];

	for (int i = 0; i < 20; i++)
	{
		arrayOfSegments[i].setPoints(0, 0);
	}

	int X = sizeOfSegment / 2 + sizeOfSegment;
	int Y = sizeOfSegment / 2 + sizeOfSegment;
	int chekcker = 1;
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			arrayOfSegments[chekcker].setPoints(X, Y);
			chekcker++;
#ifdef _DEBUG
			cout << "X = " << X << endl;
			cout << "Y = " << Y << endl;
#endif // DEBUG
			X = X + sizeOfSegment;
		}
		Y = Y + sizeOfSegment;
		X = sizeOfSegment / 2 + sizeOfSegment;
	}

	int choise1 = 20;
	int choise2 = 20;
	int choise3 = 20;
	int choise4 = 20;
	int choise5 = 20;
	int choise6 = 20;
	int choise7 = 20;
	int choise8 = 20;
	int choise9 = 20;
	int choise10 = 20;
	int choise11 = 20;
	int choise12 = 20;
	int choise13 = 20;
	int choise14 = 20;
	int choise15 = 20;
	int choise16 = 20;

	/*for (int i = 0; i < 100; i++)
	{
		int k = d8.randomize(100);
	}*/

	for (int i = 0; i < (1600 - (16 * percentOfWater))/100; i++)
	{
		int randomSegment = 0;
		bool gotIt = false;

		do
		{
			gotIt = false;
			randomSegment = d8.randomize(15999)/1000 + 1;
			if (randomSegment > 3 && d8.randomize(100) > 57)
			{
				randomSegment -= (d8.randomize(300) / 100);
			}
			cout << "random segment selector = " << randomSegment << endl;
			if (randomSegment == choise1)
			{
				gotIt = true;
				cout << "Choise1 match  " << endl;
			}
			if (randomSegment == choise2)
			{
				gotIt = true;
				cout << "Choise2 match  " << endl;
			}
			if (randomSegment == choise3)
			{
				gotIt = true;
				cout << "Choise3 match  " << endl;
			}
			if (randomSegment == choise4)
			{
				gotIt = true;
				cout << "Choise4 match  " << endl;
			}
			if (randomSegment == choise5)
			{
				gotIt = true;
				cout << "Choise5 match  " << endl;
			}
			if (randomSegment == choise6)
			{
				gotIt = true;
				cout << "Choise6 match  " << endl;
			}
			if (randomSegment == choise7)
			{
				gotIt = true;
				cout << "Choise7 match  " << endl;
			}
			if (randomSegment == choise8)
			{
				gotIt = true;
				cout << "Choise8 match  " << endl;
			}
			if (randomSegment == choise9)
			{
				gotIt = true;
				cout << "Choise9 match  " << endl;
			}
			if (randomSegment == choise10)
			{
				gotIt = true;
				cout << "Choise10 match  " << endl;
			}
			if (randomSegment == choise11)
			{
				gotIt = true;
				cout << "Choise11 match  " << endl;
			}
			if (randomSegment == choise12)
			{
				gotIt = true;
				cout << "Choise12 match  " << endl;
			}
			if (randomSegment == choise13)
			{
				gotIt = true;
				cout << "Choise13 match  " << endl;
			}
			if (randomSegment == choise14)
			{
				gotIt = true;
				cout << "Choise14 match  " << endl;
			}
			if (randomSegment == choise15)
			{
				gotIt = true;
				cout << "Choise15 match  " << endl;
			}
			if (randomSegment == choise16)
			{
				gotIt = true;
				cout << "Choise16 match  " << endl;
			}

		} while (gotIt == true);
		
		switch (i)
		{
		case 0:
			choise1 = randomSegment;
			cout << "Choise1 =  " << choise1 << endl;
			break;
		case 1:
			choise2 = randomSegment;
			cout << "Choise2 =  " << choise2 << endl;
			break;
		case 2:
			choise3 = randomSegment;
			cout << "Choise3 =  " << choise3 << endl;
			break;
		case 3:
			choise4 = randomSegment;
			cout << "Choise4 =  " << choise4 << endl;
			break;
		case 4:
			choise5 = randomSegment;
			cout << "Choise5 =  " << choise5 << endl;
			break;
		case 5:
			choise6 = randomSegment;
			cout << "Choise6 =  " << choise6 << endl;
			break;
		case 6:
			choise7 = randomSegment;
			cout << "Choise7 =  " << choise7 << endl;
			break;
		case 7:
			choise8 = randomSegment;
			cout << "Choise8 =  " << choise8 << endl;
			break;
		case 8:
			choise9 = randomSegment;
			cout << "Choise9 =  " << choise9 << endl;
			break;
		case 9:
			choise10 = randomSegment;
			cout << "Choise10 =  " << choise10 << endl;
			break;
		case 10:
			choise11 = randomSegment;
			cout << "Choise11 =  " << choise11 << endl;
			break;
		case 11:
			choise12 = randomSegment;
			cout << "Choise12 =  " << choise12 << endl;
			break;
		case 12:
			choise13 = randomSegment;
			cout << "Choise13 =  " << choise13 << endl;
			break;
		case 13:
			choise14 = randomSegment;
			cout << "Choise14 =  " << choise14 << endl;
			break;
		case 14:
			choise15 = randomSegment;
			cout << "Choise15 =  " << choise15 << endl;
			break;
		case 15:
			choise16 = randomSegment;
			cout << "Choise16 =  " << choise16 << endl;
			break;
		}
		cout << "#";
		X = arrayOfSegments[randomSegment].get_pnt1();
		Y = arrayOfSegments[randomSegment].get_pnt2();
		scope.moveToPnt(X, Y);
		scope.set_elem(mountain);
		cout << "#" << endl;
		for (int j = 0; j < sizeOfSegment/(100 - (percentOfWater/2) + 1); j++)
		{
			int heetX = d8.randomize(sizeOfSegment / (d8.randomize(3000) / 100 + 1));
			int heetY = d8.randomize(sizeOfSegment / (d8.randomize(3000) / 100 + 1));
			int x = 0;
			int y = 0;
			if (d8.randomize(100) < 50)
			{
				x = X + heetX;
			}
			else
			{
				x = X - heetX;
			}
			if (d8.randomize(100) < 50)
			{
				y = Y + heetY;
			}
			else
			{
				y = Y - heetY;
			}

			scope.moveToPnt(x, y);

			scope.set_elem(mountain);

			cout << "#";
		}

		//this->constrLand(X - sizeOfSegment / 2, Y - sizeOfSegment / 2, sizeOfSegment, sizeOfSegment, 0, "randomize");
	
		cout << "#" << endl;
	}
	
	int j = (sizeOfSegment/100)*(4 - (percentOfWater/25));

	cout << "Mountains constructing begins:" << endl;

	for (int i = 0; i < 1; i++)
	{
		cout << "#";
		this->constrLand(0, 0, terrSize, terrSize, mountain, "none");
	}
	for (int i = 0; i < j; i++)
	{
		cout << "#";
		this->constrLand(0, 0, terrSize, terrSize, mountain, "randomize");
	}
	cout << "#" << endl;
	cout << "Mountains complete" << endl;

	j = (sizeOfSegment / 100) * (20 - (percentOfWater / 5));

	cout << "Highlands constructing begins:" << endl;

	for (int i = 0; i < 1; i++)
	{
		cout << "#";
		this->constrLand(0, 0, terrSize, terrSize, highland, "none");
	}
	for (int i = 0; i < j; i++)
	{
		cout << "#";
		this->constrLand(0, 0, terrSize, terrSize, highland, "randomize");
	}
	cout << "#" << endl;
	cout << "Highlands complete" << endl;
	
	j = (sizeOfSegment / 100) * (50 - (percentOfWater / 2));
	
	cout << "Middlelands constructing begins:" << endl;

	for (int i = 0; i < 1; i++)
	{
		cout << "#";
		this->constrLand(0, 0, terrSize, terrSize, midland, "none");
		//this->spiralGen(terrSize, terrSize/2, terrSize/2, midland);
	}
	for (int i = 0; i < j; i++)
	{
		cout << "#";
		this->constrLand(0, 0, terrSize, terrSize, midland, "randomize");
		//this->spiralGen(terrSize, terrSize/2, terrSize/2, midland);
	}
	cout << "#" << endl;
	cout << "Middlelands complete" << endl;

	j = (sizeOfSegment / 100) * (25 - (percentOfWater / 4));

	cout << "Lowlands constructing begins:" << endl;

	for (int i = 0; i < 1; i++)
	{
		cout << "#";
		this->constrLand(0, 0, terrSize, terrSize, lowland, "none");
		//this->spiralGen(terrSize, terrSize/2, terrSize/2, midland);
	}
	for (int i = 0; i < j; i++)
	{
		cout << "#";
		this->constrLand(0, 0, terrSize, terrSize, lowland, "randomize");
		//this->spiralGen(terrSize, terrSize/2, terrSize/2, midland);
	}
	
	cout << "#" << endl;
	cout << "Lowlands complete" << endl;

	for (int y = 0; y < terrSize; y++)
	{
		for (short x = 0; x < terrSize; x++)
		{
			scope.moveToPnt(x, y);
			if (scope.get_elem() != nowidth)
			{
				scope.set_elem(lowland);
			}
		}
	}

/*	j = (sizeOfSegment / 100) * (5 - (percentOfWater / 20));

	cout << "Water constructing begins:" << endl;

	for (int i = 0; i < j; i++)
	{
		cout << "#";
		this->constrLand(0, 0, terrSize, terrSize, lowland, "randomize");
		//this->spiralGen(terrSize, terrSize/2, terrSize/2, midland);
	}
	cout << "#" << endl;
	cout << "Water complete" << endl;

	/*
	for (int i = 0; i < terrSize; i++)
	{
		for (int j = 0; j < terrSize; j++)
		{
			scope.moveToPnt(j, i);
			if (scope.get_elem() != nowidth && scope.get_elem() != mountain)
			{
				if (this->ScopeScaner(nowidth, 5, 0, 0) == true)
				{
					scope.set_elem(lowland);
				}
			}
		}
	}*/
	cout << "#" << endl;
}