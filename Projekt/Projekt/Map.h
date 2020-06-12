#pragma once
#include "windows.h"
#include "Unit.h"
#include <vector>
#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

	class Map
	{
		char** map; //array with unit's points
		int x; //width of map
		int y; //height of map

	public:
		Map(int = 20, int = 10);
		~Map();

		int getX(); //Gets variable 'x'
		int getY(); //Gets variable 'y'
		char getMap(int, int); //Gets certain element from array
		void setMap(int, int, char); //Used for updating certain element in array
		void draw(); //Draws the map in console
		bool IsOccupied(vector <Unit*>, vector <Unit*>, int, int, int, char); //Returns true if a position is already occupied by a different unit
	};

